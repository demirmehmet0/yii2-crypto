<?php
use \portalium\theme\widgets\GridView;
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
    'title' => \demirmehmet\crypto\Module::t('Matrix Parameter'),
    'actions' => [
        'header' => [

        ],
        'footer' => [
            \portalium\theme\helpers\Html::submitButton('Submit', ['class' => 'btn btn-primary'])
        ]
    ]
]);
echo $form->field($model, 'inputfilename')->fileInput()->label('Input File');
echo $form->field($model, 'max_time')->textInput(['maxlength' => true])->label('Max Time');
/* chosen_param
threshold
depth_limit */
echo $form->field($model, 'chosen_param')->textInput(['maxlength' => true])->label('Chosen Param');
echo $form->field($model, 'threshold')->textInput(['maxlength' => true])->label('Threshold');
echo $form->field($model, 'depth_limit')->textInput(['maxlength' => true])->label('Depth Limit');

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
        ],
        'bodyOptions' => [
            'style' => 'max-height: 270px; overflow-y: auto;'
        ]
    ]);
    echo \portalium\theme\widgets\Html::beginTag('p', ['style' => 'white-space: pre;']);
    echo str_replace("\n", "<br>", $response);
    echo \portalium\theme\widgets\Html::endTag('p');
    
    \portalium\theme\widgets\Panel::end();
    echo \portalium\theme\widgets\Html::endTag('div');


}

echo \portalium\theme\widgets\Html::endTag('div');
echo \portalium\theme\widgets\Html::endTag('div');

\portalium\theme\widgets\ActiveForm::end();

?>