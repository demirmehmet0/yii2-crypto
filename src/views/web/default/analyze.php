<?php

use kartik\grid\GridView;

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
echo $form->field($model, 'bit_num')->textInput(['maxlength' => true])->label('Bit Number');

\portalium\theme\widgets\Panel::end();
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
    echo GridView::widget([
        'dataProvider' => $dataProvider,
        'autoXlFormat' => true,
        'toggleDataContainer' => ['class' => 'btn-group mr-2 me-2'],
        'export' => [
            'showConfirmAlert' => true,
            'target' => GridView::TARGET_BLANK
        ],
        'columns' => [
            ['class' => 'yii\grid\SerialColumn'],
//            'Sbox',
            [
                'attribute' => 'Sbox',
                'format' => 'raw',
                'value' => function ($model) {
                    return '<i class="fa fa-eye" data-bs-toggle="tooltip" data-bs-placement="top" title="' . $model['Sbox'] . '" onclick="navigator.clipboard.writeText(\'' . $model['Sbox'] . '\').then(() => {alert(\'' . $model['Sbox'] . '\')})"></i>';
                }
            ],
            'MaxDDT',
            'MaxLAT',
            'AlgebraicDegree',
            'FixedPoints',
            'BIBO_Pattern',
            'LinearBranchNumber',
            'DifferentialBranchNumber',
            'FrequencyOfDifferentialUnif',
            'FrequencyOfLinearity',
            'BCT_Uniformity',
            'DLCT_Uniformity',
            'NLM',
            'NLM_Percentage',
            'IsInvolution'
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
echo \portalium\theme\widgets\Html::endTag('div');

\portalium\theme\widgets\ActiveForm::end();

?>
<script defer src="https://use.fontawesome.com/releases/v5.3.1/js/all.js" crossorigin="anonymous"></script>
