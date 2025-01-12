tatic gatenum create_circuit(state *st, const ttable target, const ttable mask,
    const int8_t *inbits, const options *opt) {

  gatenum gate_order[MAX_GATES];
  for (int i = 0; i < st->num_gates; i++) {
    gate_order[i] = st->num_gates - 1 - i;
  }
  //print available gates

  for (int i = 0; opt->avail_gates[i].num_inputs != 0; i++) {
      printf("%s ", gate_name[opt->avail_gates[i].fun]);
    }

  /* Randomize the gate search order. */
  if (opt->randomize) {
    /* Fisher-Yates shuffle. */
    for (uint32_t i = st->num_gates - 1; i > 0; i--) {
      uint64_t j = xorshift1024() % (i + 1);
      gatenum t = gate_order[i];
      gate_order[i] = gate_order[j];
      gate_order[j] = t;
    }
  }

  /* 1. Look through the existing circuit. If there is a gate that produces the desired map, simply
     return the ID of that gate. */

  for (int i = 0; i < st->num_gates; i++) {
    if (ttable_equals_mask(target, st->gates[gate_order[i]].table, mask)) {
      ASSERT_AND_RETURN(gate_order[i], target, st, mask);
    }
  }

  /* 2. If there are any gates whose inverse produces the desired map, append a NOT gate, and
     return the ID of the NOT gate. */

  if (!check_num_gates_possible(st, 1, get_sat_metric(NOT), opt)) {
    return NO_GATE;
  }

  for (int i = 0; i < st->num_gates; i++) {
    if (ttable_equals_mask(target, ~st->gates[gate_order[i]].table, mask)) {
      ASSERT_AND_RETURN(add_not_gate(st, gate_order[i], opt), target, st, mask);
    }
  }

  /* 3. Look at all pairs of gates in the existing circuit. If they can be combined with a single
     gate to produce the desired map, add that single gate and return its ID. */

  if (!check_num_gates_possible(st, 1, get_sat_metric(AND), opt)) {
    return NO_GATE;
  }

  const ttable mtarget = target & mask;
  for (int i = 0; i < st->num_gates; i++) {
    const gatenum gi = gate_order[i];
    const ttable ti = st->gates[gi].table;
    for (int k = i + 1; k < st->num_gates; k++) {
      const gatenum gk = gate_order[k];
      const ttable tk = st->gates[gk].table;
      for (int m = 0; opt->avail_gates[m].num_inputs != 0; m++) {
        if (ttable_equals(mtarget, generate_ttable_2(opt->avail_gates[m].fun, ti, tk))) {
          ASSERT_AND_RETURN(add_boolfunc_2(st, &opt->avail_gates[m], gi, gk, opt), target, st,
              mask);
        }
        if (!opt->avail_gates[m].ab_commutative) {
          if (ttable_equals(mtarget, generate_ttable_2(opt->avail_gates[m].fun, tk, ti))) {
            ASSERT_AND_RETURN(add_boolfunc_2(st, &opt->avail_gates[m], gk, gi, opt), target, st,
                mask);
          }
        }
      }
    }
  }

  if (opt->lut_graph) {
    gatenum ret = lut_search(st, target, mask, inbits, gate_order, opt);
    if (ret != NO_GATE) {
      ASSERT_AND_RETURN(ret, target, st, mask);
    }
  } else {
    /* 4. Look at all combinations of two or three gates in the circuit. If they can be combined
       with two gates to produce the desired map, add the gates, and return the ID of the one that
       produces the desired map. */

    if (!check_num_gates_possible(st, 2, get_sat_metric(AND) + get_sat_metric(NOT), opt)) {
      return NO_GATE;
    }

    /* All combinations of two gates. */
    for (int i = 0; i < st->num_gates; i++) {
      const gatenum gi = gate_order[i];
      ttable ti = st->gates[gi].table;
      for (int k = i + 1; k < st->num_gates; k++) {
        const gatenum gk = gate_order[k];
        ttable tk = st->gates[gk].table;
        for (int m = 0; opt->avail_not[m].num_inputs != 0; m++) {
          if (ttable_equals(mtarget, generate_ttable_2(opt->avail_not[m].fun, ti, tk))) {
            ASSERT_AND_RETURN(add_boolfunc_2(st, &opt->avail_not[m], gi, gk, opt), target, st,
                mask);
          }
          if (!opt->avail_not[m].ab_commutative) {
            if (ttable_equals(mtarget, generate_ttable_2(opt->avail_not[m].fun, tk, ti))) {
              ASSERT_AND_RETURN(add_boolfunc_2(st, &opt->avail_not[m], gk, gi, opt), target, st,
                  mask);
            }
          }
        }
      }
    }

    if (!check_num_gates_possible(st, 3, 2 * get_sat_metric(AND) + get_sat_metric(NOT), opt)) {
      return NO_GATE;
    }

    /* All combinations of three gates. */
    for (int i = 0; i < st->num_gates; i++) {
      const gatenum gi = gate_order[i];
      ttable ti = st->gates[gi].table;
      for (int k = i + 1; k < st->num_gates; k++) {
        const gatenum gk = gate_order[k];
        ttable tk = st->gates[gk].table;
        for (int m = k + 1; m < st->num_gates; m++) {
          const gatenum gm = gate_order[m];
          ttable tm = st->gates[gm].table;
          const ttable tables[] = {ti, tk, tm};
          if (!check_n_lut_possible(3, target, mask, tables)) {
            continue;
          }
          for (int p = 0; opt->avail_3[p].num_inputs != 0; p++) {
            if (ttable_equals_mask(target, generate_ttable_3(opt->avail_3[p], ti, tk, tm), mask)) {
              ASSERT_AND_RETURN(add_boolfunc_3(st, &opt->avail_3[p], gi, gk, gm, opt), target, st,
                  mask);
            }
            if (!opt->avail_3[m].ab_commutative) {
              if (ttable_equals_mask(target, generate_ttable_3(opt->avail_3[p], tk, ti, tm),
                  mask)) {
                ASSERT_AND_RETURN(add_boolfunc_3(st, &opt->avail_3[p], gk, gi, gm, opt), target, st,
                    mask);
              }
            }
            if (!opt->avail_3[m].ac_commutative) {
              if (ttable_equals_mask(target, generate_ttable_3(opt->avail_3[p], tm, tk, ti),
                  mask)) {
                ASSERT_AND_RETURN(add_boolfunc_3(st, &opt->avail_3[p], gm, gk, gi, opt), target, st,
                    mask);
              }
            }
            if (!opt->avail_3[m].bc_commutative) {
              if (ttable_equals_mask(target, generate_ttable_3(opt->avail_3[p], ti, tm, tk),
                  mask)) {
                ASSERT_AND_RETURN(add_boolfunc_3(st, &opt->avail_3[p], gi, gm, gk, opt), target, st,
                    mask);
              }
            }
          }
        }
      }
    }
  } /* End of if (opt->lut_graph)... */

  /* 5. Use the specified input bit to select between two Karnaugh maps. Call this function
     recursively to generate those two maps. */

  /* Copy input bits already used to new array to avoid modifying the old one. */
  int8_t next_inbits[8];
  uint8_t bitp = 0;
  while (bitp < 6 && inbits[bitp] != -1) {
    next_inbits[bitp] = inbits[bitp];
    bitp += 1;
  }
  assert(bitp < 7);
  next_inbits[bitp] = -1;
  next_inbits[bitp + 1] = -1;

  state best;
  gatenum best_out = NO_GATE;
  best.num_gates = 0;
  best.sat_metric = 0;

  /* Try all input bit orders. */
  for (int bit = 0; bit < get_num_inputs(st); bit++) {
    /* Skip input bits that have already been used for multiplexing. */
    bool skip = false;
    for (int i = 0; i < bitp; i++) {
      if (inbits[i] == bit) {
        skip = true;
        break;
      }
    }
    if (skip == true) {
      continue;
    }
    next_inbits[bitp] = bit;

    const ttable fsel = st->gates[bit].table; /* Selection bit. */
    state nst;
    gatenum nst_out;
    if (opt->lut_graph) { /* Use a LUT-based multiplexer. */
      nst = *st;
      nst.max_gates -= 1; /* A multiplexer will have to be added later. */
      gatenum fb = create_circuit(&nst, target, mask & ~fsel, next_inbits, opt);
      if (fb == NO_GATE) {
        continue;
      }
      assert(ttable_equals_mask(target, nst.gates[fb].table, mask & ~fsel));
      gatenum fc = create_circuit(&nst, target, mask & fsel, next_inbits, opt);
      if (fc == NO_GATE) {
        continue;
      }
      assert(ttable_equals_mask(target, nst.gates[fc].table, mask & fsel));
      nst.max_gates += 1;

      if (fb == fc) {
        nst_out = fb;
        assert(ttable_equals_mask(target, nst.gates[nst_out].table, mask));
      } else if (fb == bit) {
        nst_out = add_and_gate(&nst, fb, fc, opt);
        if (nst_out == NO_GATE) {
          continue;
        }
        assert(ttable_equals_mask(target, nst.gates[nst_out].table, mask));
      } else if (fc == bit) {
        nst_out = add_or_gate(&nst, fb, fc, opt);
        if (nst_out == NO_GATE) {
          continue;
        }
        assert(ttable_equals_mask(target, nst.gates[nst_out].table, mask));
      } else {
        ttable mux_table = generate_lut_ttable(0xac, nst.gates[bit].table, nst.gates[fb].table,
            nst.gates[fc].table);
        nst_out = add_lut(&nst, 0xac, mux_table, bit, fb, fc);
        if (nst_out == NO_GATE) {
          continue;
        }
        assert(ttable_equals_mask(target, nst.gates[nst_out].table, mask));
      }
      assert(ttable_equals_mask(target, nst.gates[nst_out].table, mask));
    } else { /* Not a LUT graph. Test both AND- and OR-based multiplexers. */
      state nst_and = *st; /* New state using AND multiplexer. */

      /* A multiplexer will have to be added later. */
      nst_and.max_gates -= 2;
      nst_and.max_sat_metric -= get_sat_metric(AND) + get_sat_metric(XOR);

      gatenum fb = create_circuit(&nst_and, target & ~fsel, mask & ~fsel, next_inbits, opt);
      assert(fb == NO_GATE || ttable_equals_mask(target, nst_and.gates[fb].table, mask & ~fsel));
      gatenum mux_out_and = NO_GATE;
      if (fb != NO_GATE) {
        gatenum fc = create_circuit(&nst_and, nst_and.gates[fb].table ^ target, mask & fsel,
            next_inbits, opt);
        assert(fc == NO_GATE || ttable_equals_mask(nst_and.gates[fb].table ^ target,
            nst_and.gates[fc].table, mask & fsel));
        /* Add back subtracted max from above. */
        nst_and.max_gates += 2;
        nst_and.max_sat_metric += get_sat_metric(AND) + get_sat_metric(XOR);
        gatenum andg = add_and_gate(&nst_and, fc, bit, opt);
        mux_out_and = add_xor_gate(&nst_and, fb, andg, opt);
        assert(mux_out_and == NO_GATE ||
            ttable_equals_mask(target, nst_and.gates[mux_out_and].table, mask));
      }

      state nst_or = *st; /* New state using OR multiplexer. */
      if (mux_out_and != NO_GATE) {
        nst_or.max_gates = nst_and.num_gates;
        nst_or.max_sat_metric = nst_and.sat_metric;
      }

      /* A multiplexer will have to be added later. */
      nst_or.max_gates -= 2;
      nst_or.max_sat_metric -= get_sat_metric(OR) + get_sat_metric(XOR);

      gatenum fd = create_circuit(&nst_or, ~target & fsel, mask & fsel, next_inbits, opt);
      assert(fd == NO_GATE || ttable_equals_mask(~target & fsel, nst_or.gates[fd].table,
          mask & fsel));
      gatenum mux_out_or = NO_GATE;
      if (fd != NO_GATE) {
        gatenum fe = create_circuit(&nst_or, nst_or.gates[fd].table ^ target, mask & ~fsel,
            next_inbits, opt);
        assert(fe == NO_GATE || ttable_equals_mask(nst_or.gates[fd].table ^ target,
            nst_or.gates[fe].table, mask & ~fsel));
        /* Add back subtracted max from above. */
        nst_or.max_gates += 2;
        nst_or.max_sat_metric += get_sat_metric(AND) + get_sat_metric(XOR);
        gatenum org = add_or_gate(&nst_or, fe, bit, opt);
        mux_out_or = add_xor_gate(&nst_or, fd, org, opt);
        assert(mux_out_or == NO_GATE ||
            ttable_equals_mask(target, nst_or.gates[mux_out_or].table, mask));
        nst_or.max_gates = st->max_gates;
        nst_or.max_sat_metric = st->max_sat_metric;
      }
      if (mux_out_and == NO_GATE && mux_out_or == NO_GATE) {
        continue;
      }

      if (opt->metric == GATES) {
        if (mux_out_or == NO_GATE
            || (mux_out_and != NO_GATE && nst_and.num_gates < nst_or.num_gates)) {
          nst = nst_and;
          nst_out = mux_out_and;
        } else {
          nst = nst_or;
          nst_out = mux_out_or;
        }
      } else {
        if (mux_out_or == NO_GATE
            || (mux_out_and != NO_GATE && nst_and.sat_metric < nst_or.sat_metric)) {
          nst = nst_and;
          nst_out = mux_out_and;
        } else {
          nst = nst_or;
          nst_out = mux_out_or;
        }
      }
    } /* End of if (opt->lut_graph)... New state in nst. */

    /* Compare nst to best. */
    assert(best.num_gates == 0 || ttable_equals_mask(target, best.gates[best_out].table, mask));
    if (opt->metric == GATES) {
      if (best.num_gates == 0 || nst.num_gates < best.num_gates) {
        best = nst;
        best_out = nst_out;
      }
    } else {
      if (best.sat_metric == 0 || nst.sat_metric < best.sat_metric) {
        best = nst;
        best_out = nst_out;
      }
    }
    assert(best.num_gates == 0 || ttable_equals_mask(target, best.gates[best_out].table, mask));
  } /* End of for loop over all input bits. */

  if (best.num_gates == 0) {
    return NO_GATE;
  }

  assert(ttable_equals_mask(target, best.gates[best_out].table, mask));
  *st = best;
  return best_out;
}