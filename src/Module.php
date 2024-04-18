<?php

namespace demirmehmet\crypto;

use portalium\base\Event;
use demirmehmet\crypto\components\TriggerActions;

class Module extends \portalium\base\Module
{
    public static $tablePrefix = 'crypto_';
    
    public static $name = 'crypto';

    public static $description = 'crypto Module';

    public $apiRules = [
        [
            'class' => 'yii\rest\UrlRule',
            'controller' => [
                'crypto/default',
            ]
        ],
    ];
    
    public static function moduleInit()
    {
        self::registerTranslation('crypto','@demirmehmet/crypto/messages',[
            'crypto' => 'crypto.php',
        ]);
    }

    public static function t($message, array $params = [])
    {
        return parent::coreT('crypto', $message, $params);
    }

}