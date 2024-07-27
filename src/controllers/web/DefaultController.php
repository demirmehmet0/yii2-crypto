<?php

namespace demirmehmet\crypto\controllers\web;

use http\Client;
use portalium\web\Controller as WebController;
use Yii;
use yii\base\DynamicModel;

class DefaultController extends WebController
{
    public function behaviors()
    {
        $behaviors = parent::behaviors();
//        $behaviors['access']['except'] = ['index', 'download', 'analyze'];
//        $behaviors['access']['rules'] = [
//            [
//                'allow' => true,
//                'roles' => ['*'],
//            ],
//        ];

        return $behaviors;
    }

    public function actionIndex()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'max_cost' => '',
//            'mutationRatio' => '',
//            'mutationRepeat' => '',
//            'searchoption' => '',
//            'outputfilename' => '',
//            'fixedpoint' => '',
        ]);
        $model->addRule(['inputfilename', 'max_cost'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/sbox-gen')
                ->setFormat(\yii\httpclient\Client::FORMAT_JSON)
                ->setOptions([
                    'timeout' => 60,
                ])
                ->setData([
                    'filename' => $file->name,
                    'max_cost' => $model->max_cost,
                ])
                ->addFile('file', $file->tempName, ['filename' => $file->name])
                ->send();
            \Yii::warning($response->content, 'crypto');
            $response = json_decode($response->content, true);
//            download file
            $new_file = $this->save_file($response, $file->name);
            \Yii::warning($new_file, 'crypto');
            $response = json_decode($response, true);
            $dataProvider = new \yii\data\ArrayDataProvider([
                'allModels' => $response,
                'pagination' => false
            ]);
            
            return $this->render('index', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name,
                'dataProvider' => $dataProvider,
            ]);
        }

        return $this->render('index', [
                'model' => $model,
            ]
        );
    }

    public function actionAnalyze()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'bit_num' => '',
        ]);
        $model->addRule(['inputfilename', 'bit_num'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/sbox-analyze')
                ->setFormat(\yii\httpclient\Client::FORMAT_JSON)
                ->setOptions([
                    'timeout' => 60,
                ])
                ->setData([
                    'filename' => $file->name,
                    'bit_num' => $model->bit_num,
                ])
                ->addFile('file', $file->tempName, ['filename' => $file->name])
                ->send();
            \Yii::warning($response->content, 'crypto');
//            download file
            $response = json_decode($response->content, true);
            
            $new_file = $this->save_file($response, $file->name);
            
            \Yii::warning($new_file, 'crypto');

        // [
        //    {
        //        "Sbox": "0,10,17,9,22,28,6,19,24,3,1,13,27,11,18,23,21,2,14,7,25,16,4,15,8,20,30,12,5,31,26,29",
        //        "MaxDDT": "4",
        //        "MaxLAT": "6",
        //        "AlgebraicDegree": "3",
        //        "FixedPoints": "2",
        //        "BIBO_Pattern": "31",
        //        "LinearBranchNumber": "2",
        //        "DifferentialBranchNumber": "2",
        //        "FrequencyOfDifferentialUnif": "51",
        //        "FrequencyOfLinearity": "64",
        //        "BCT_Uniformity": "10",
        //        "DLCT_Uniformity": "16",
        //        "NLM": "10",
        //        "NLM_Percentage": "83",
        //        "IsInvolution": "1"
        //    },
        //    {
        //        "Sbox": "0,10,17,9,22,28,6,19,24,3,1,30,27,26,18,23,21,2,14,7,25,16,4,15,8,20,13,12,5,31,11,29",
        //        "MaxDDT": "4",
        //        "MaxLAT": "6",
        //        "AlgebraicDegree": "3",
        //        "FixedPoints": "2",
        //        "BIBO_Pattern": "29",
        //        "LinearBranchNumber": "2",
        //        "DifferentialBranchNumber": "2",
        //        "FrequencyOfDifferentialUnif": "51",
        //        "FrequencyOfLinearity": "64",
        //        "BCT_Uniformity": "10",
        //        "DLCT_Uniformity": "16",
        //        "NLM": "10",
        //        "NLM_Percentage": "83",
        //        "IsInvolution": "1"
        //    }]
            
//            result convert to array for gridview
            $response = json_decode($response, true);
            $dataProvider = new \yii\data\ArrayDataProvider([
                'allModels' => $response,
                'pagination' => false
            ]);
            
            return $this->render('analyze', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name,
                'dataProvider' => $dataProvider,
            ]);
        }

        return $this->render('analyze', [
                'model' => $model,
            ]
        );
    }

    public function actionSbp()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'max_time' => '',
            'chosen_param' => '',
            'threshold' => '',
            'depth_limit' => '',
        ]);
        $model->addRule(['inputfilename', 'max_time', 'chosen_param', 'threshold', 'depth_limit'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/sbp')
                ->setFormat(\yii\httpclient\Client::FORMAT_JSON)
                ->setOptions([
                    'timeout' => 60,
                ])
                ->setData([
                    'filename' => $file->name,
                    'max_time' => $model->max_time,
                    'chosen_param' => $model->chosen_param,
                    'threshold' => $model->threshold,
                    'depth_limit' => $model->depth_limit,
                ])
                ->addFile('file', $file->tempName, ['filename' => $file->name])
                ->send();
            \Yii::warning($response->content, 'crypto');
//            download file
            $response = json_decode($response->content, true);

            $new_file = $this->save_file($response, $file->name);

            \Yii::warning($new_file, 'crypto');


            return $this->render('sbp', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render('sbp', [
                'model' => $model,
            ]
        );
    }

    public function actionDbBdkci()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'max_iteration' => '',
        ]);
        $model->addRule(['inputfilename', 'max_iteration'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/db-bdkci')
                ->setFormat(\yii\httpclient\Client::FORMAT_JSON)
                ->setOptions([
                    'timeout' => 60,
                ])
                ->setData([
                    'filename' => $file->name,
                    'max_iteration' => $model->max_iteration,
                ])
                ->addFile('file', $file->tempName, ['filename' => $file->name])
                ->send();
            \Yii::warning($response->content, 'crypto');
//            download file
            $response = json_decode($response->content, true);

            $new_file = $this->save_file($response, $file->name);

            \Yii::warning($new_file, 'crypto');

            return $this->render('db-bdkci', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render('db-bdkci', [
                'model' => $model,
            ]
        );
    }

    
    public function save_file($content, $filename)
    {
        $path = realpath(Yii::$app->basePath . '/../data');
        $new_file = $path . '/' . $filename;
        file_put_contents($new_file, $content);
        return $new_file;
    }
    
    public function actionDownload($filename)
    {
        $path = realpath(Yii::$app->basePath . '/../data');
        $file = $path . '/' . $filename;
        if (file_exists($file)) {
            return Yii::$app->response->sendFile($file);
        }
    }
}