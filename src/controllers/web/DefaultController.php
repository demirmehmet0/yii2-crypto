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
        ]);

        $model->addRule(['inputfilename', 'max_cost'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');

            $pythonfile = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/sbox_gen.py');

            $new_file = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/data') . '/' . $file->name;

            file_put_contents($new_file, file_get_contents($file->tempName));
            $command = 'python3 ' . $pythonfile . ' ' . $new_file . ' ' . $model->max_cost;

            $response = shell_exec($command);

            $response = json_decode($response, true);

//            zip file /vendor/demirmehmet/yii2-crypto/src/scripts/results/newlut
            $zipname = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/results/' . str_replace('.txt', '', $file->name) . '.zip');
            $folder = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/results/' . str_replace('.txt', '', $file->name));
            exec('zip -r ' . $zipname . ' ' . $folder);
//            copy zip file to data
            copy($zipname, Yii::$app->basePath . '/../data/' . str_replace('.txt', '', $file->name) . '.zip');
            $dataProvider = new \yii\data\ArrayDataProvider([
                'allModels' => $response,
                'pagination' => false
            ]);

            return $this->render('index', [
                'model' => $model,
                'response' => $response,
                'new_file' => str_replace('.txt', '', $file->name) . '.zip',
                'dataProvider' => $dataProvider,
            ]);
        }

        return $this->render(
            'index',
            [
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
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            /* $client = new \yii\httpclient\Client();
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
            
            \Yii::warning($new_file, 'crypto'); */
            $pythonfile = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/sbox_analyze.py');

            $new_file = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/data') . '/' . $file->name;

            file_put_contents($new_file, file_get_contents($file->tempName));
            $command = 'python3 ' . $pythonfile . ' ' . $new_file . ' ' . $model->bit_num;

            $response = shell_exec($command);
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

        return $this->render(
            'analyze',
            [
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
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            /* $client = new \yii\httpclient\Client();
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
            \Yii::warning($response->content, 'crypto'); */

            $pythonfile = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/db_bdkci.py');

            $new_file = Yii::getAlias('@vendor/demirmehmet/yii2-crypto/src/scripts/data/matrix') . '/' . $file->name;
            $this->save_file(file_get_contents($file->tempName), './../../../'.$new_file);
            $command = 'python3 ' . $pythonfile . ' ' . $new_file . ' ' . $model->max_iteration;
            $response = shell_exec($command);
            var_dump($response);
            $response = json_decode($response, true);
            var_dump($response);
            return $this->render('db-bdkci', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'db-bdkci',
            [
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

        return $this->render(
            'sbp',
            [
                'model' => $model,
            ]
        );
    }


    public function actionA1()
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
                ->setUrl('http://185.149.103.143:5000/a1')
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

            return $this->render('a1', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'a1',
            [
                'model' => $model,
            ]
        );
    }

    public function actionA2()
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
                ->setUrl('http://185.149.103.143:5000/a2')
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

            return $this->render('a2', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'a2',
            [
                'model' => $model,
            ]
        );
    }

    public function actionBfi()
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
                ->setUrl('http://185.149.103.143:5000/bfi')
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

            return $this->render('bfi', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'bfi',
            [
                'model' => $model,
            ]
        );
    }

    public function actionBp()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'max_iteration' => '',
            'threshold' => '',
            'depth_limit' => '',
        ]);
        $model->addRule(['inputfilename', 'max_iteration', 'threshold'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/bp')
                ->setFormat(\yii\httpclient\Client::FORMAT_JSON)
                ->setOptions([
                    'timeout' => 60,
                ])
                ->setData([
                    'filename' => $file->name,
                    'max_iteration' => $model->max_iteration,
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

            return $this->render('bp', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'bp',
            [
                'model' => $model,
            ]
        );
    }

    public function actionLwfwsw()
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
                ->setUrl('http://185.149.103.143:5000/lwfwsw')
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

            return $this->render('lwfwsw', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'lwfwsw',
            [
                'model' => $model,
            ]
        );
    }

    public function actionPaar1()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'max_iteration' => '',
            'threshold' => '',
        ]);
        $model->addRule(['inputfilename', 'max_iteration', 'threshold'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/paar1')
                ->setFormat(\yii\httpclient\Client::FORMAT_JSON)
                ->setOptions([
                    'timeout' => 60,
                ])
                ->setData([
                    'filename' => $file->name,
                    'max_iteration' => $model->max_iteration,
                    'threshold' => $model->threshold,
                ])
                ->addFile('file', $file->tempName, ['filename' => $file->name])
                ->send();
            \Yii::warning($response->content, 'crypto');
            //            download file
            $response = json_decode($response->content, true);

            $new_file = $this->save_file($response, $file->name);

            \Yii::warning($new_file, 'crypto');

            return $this->render('paar1', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'paar1',
            [
                'model' => $model,
            ]
        );
    }

    public function actionPaar2()
    {
        $model = new DynamicModel([
            'inputfilename' => '',
            'max_iteration' => '',
            'threshold' => '',
        ]);
        $model->addRule(['inputfilename', 'max_iteration', 'threshold'], 'required');
        $model->addRule(['inputfilename'], 'file');
        if ($model->load(Yii::$app->request->post())) {
            $client = new \yii\httpclient\Client();
            $file = \yii\web\UploadedFile::getInstance($model, 'inputfilename');
            $response = $client->createRequest()
                ->setMethod('POST')
                ->setUrl('http://185.149.103.143:5000/paar2')
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

            return $this->render('paar2', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'paar2',
            [
                'model' => $model,
            ]
        );
    }

    public function actionRnbp()
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
                ->setUrl('http://185.149.103.143:5000/rnbp')
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

            return $this->render('rnbp', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'rnbp',
            [
                'model' => $model,
            ]
        );
    }

    public function actionXzlbz()
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
                ->setUrl('http://185.149.103.143:5000/xzlbz')
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

            return $this->render('xzlbz', [
                'model' => $model,
                'response' => $response,
                'new_file' => $file->name
            ]);
        }

        return $this->render(
            'xzlbz',
            [
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
        } else {
            return $this->redirect(['index']);
        }
    }
}
