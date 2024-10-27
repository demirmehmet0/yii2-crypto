<?php
use kartik\grid\GridView;
use demirmehmet\crypto\Module;

$this->title = Module::t('S-Box Generation');
$this->params['breadcrumbs'][] = $this->title;
//<!-- inputfilename (5x5_4.txt) - populationsize (40000) - mutationRatio(100) - mutationRepeat(1) - searchoption (24004) (fp-ddt-lat) - outputfilename (5x5-xxxx.txt) - fixed point -1 -->
$form = \portalium\theme\widgets\ActiveForm::begin([
    'id' => 'form',
    'method' => 'post',
    'options' => [
        'class' => 'form-horizontal',
    ],
    'fieldConfig' => [
        'template' => "{label}\n<div class=\"col-sm-10\">{input}</div>\n<div class=\"col-sm-10\">{error}</div>",
        'labelOptions' => ['class' => 'col-sm-2 control-label'],
    ],
]);

echo \portalium\theme\widgets\Html::beginTag('div', ['class' => 'container']);
echo \portalium\theme\widgets\Html::beginTag('div', ['class' => 'row', 'style' => 'height: 23vh;']);
echo \portalium\theme\widgets\Html::beginTag('div', ['class' => 'col-md-12']);
\portalium\theme\widgets\Panel::begin([
    'title' => \demirmehmet\crypto\Module::t('Algorithm Parameters'),
    'actions' => [
        'header' => [

        ],
        'footer' => [
            \portalium\theme\helpers\Html::submitButton('Submit', ['class' => 'btn btn-primary'])
        ]
    ]
]);
echo $form->field($model, 'inputfilename')->fileInput()->label('Input File');
echo $form->field($model, 'max_cost')->textInput(['maxlength' => true])->label('Max Cost');
//echo $form->field($model, 'mutationRatio')->textInput(['maxlength' => true]);
//echo $form->field($model, 'mutationRepeat')->textInput(['maxlength' => true]);
//echo $form->field($model, 'searchoption')->textInput(['maxlength' => true]);
//echo $form->field($model, 'outputfilename')->textInput(['maxlength' => true]);
//echo $form->field($model, 'fixedpoint')->textInput(['maxlength' => true]);
\portalium\theme\widgets\Panel::end();
echo \portalium\theme\widgets\Html::endTag('div');


echo \portalium\theme\widgets\Html::endTag('div');
if (isset($response)) {

    echo \portalium\theme\widgets\Html::beginTag('div', ['class' => 'col-md-12', 'style' => 'height: 100%;']);
    \portalium\theme\widgets\Panel::begin([
        'title' => \demirmehmet\crypto\Module::t('Response'),
        'actions' => [
            'header' => [

            ],
            'footer' => [
//                download file
                \portalium\theme\helpers\Html::a('Download', ['download', 'filename' => $new_file], ['class' => 'btn btn-primary'])
            ]
        ]
    ]);
//    echo \portalium\theme\widgets\Html::beginTag('p', ['style' => 'white-space: pre;']);
//    echo str_replace("\n", "<br>", $response);
//    echo \portalium\theme\widgets\Html::endTag('p');
    echo \kartik\grid\GridView::widget([
        'dataProvider' => $dataProvider,
        'autoXlFormat'=>true,
        'toggleDataContainer' => ['class' => 'btn-group mr-2 me-2'],
        'export'=>[
            'showConfirmAlert'=>false,
            'target'=>GridView::TARGET_BLANK
        ],
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],
            "Index",
            //            "Cost",
            //        {'UMC 180nm': 100.61, 'TSMC 65nm': 103.5, 'Depth (GEs)': 79.5, 'Depth (Soft.)': 47.0}
            [
                'attribute' => 'Cost',
                'format' => 'raw',
                'label' => 'UMC 180nm',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["Cost"]), true)['UMC 180nm'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'Cost',
                'format' => 'raw',
                'label' => 'TSMC 65nm',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["Cost"]), true)['TSMC 65nm'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'Cost',
                'format' => 'raw',
                'label' => 'Depth (GEs)',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["Cost"]), true)['Depth (GEs)'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'Cost',
                'format' => 'raw',
                'label' => 'Depth (Soft.)',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["Cost"]), true)['Depth (Soft.)'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            "Depth",
//            "GateCounts",
//            {'AND': 7, 'OR': 13, 'NOT': 3, 'XOR': 24, 'XNOR': 0, 'NAND': 0, 'NOR': 0}	
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'AND',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['AND'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'OR',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['OR'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'NOT',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['NOT'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'XOR',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['XOR'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'XNOR',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['XNOR'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'NAND',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['NAND'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            [
                'attribute' => 'GateCounts',
                'format' => 'raw',
                'label' => 'NOR',
                'value' => function ($model) {
        try {
            return json_decode(str_replace("'", "\"", $model["GateCounts"]), true)['NOR'];
        } catch(Exception $e) {
            return "";
                    }
                }
            ],
            "Time(ms)"
        ],
        'pjax' => true,
        'showPageSummary' => true,
        'panel' => [
        'type' => 'primary',
        'heading' => 'Products'
    ]

    ]);
    \portalium\theme\widgets\Panel::end();
    echo \portalium\theme\widgets\Html::endTag('div');


}
echo \portalium\theme\widgets\Html::endTag('div');

\portalium\theme\widgets\ActiveForm::end();

?>
<script defer src="https://use.fontawesome.com/releases/v5.3.1/js/all.js" crossorigin="anonymous"></script>

