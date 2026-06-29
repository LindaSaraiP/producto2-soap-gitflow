<?php
// Ejecutar:
// composer install: php composer.phar install
// php -S localhost:8000
// http://localhost:8000/clisoap2.php?n=10

header('Content-Type: text/plain; charset=utf-8');

require_once 'vendor/autoload.php';
use Stichoza\GoogleTranslate\GoogleTranslate;

$n = isset($_GET['n']) ? intval($_GET['n']) : 10;
$wsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL";

try {
    $cliente = new SoapClient($wsdl);
    $respuesta = $cliente->NumberToWords(array("ubiNum" => $n));
    $textoIngles = trim($respuesta->NumberToWordsResult);

    $traductor = new GoogleTranslate('es', 'en');
    echo $traductor->translate($textoIngles);
} catch (Exception $e) {
    http_response_code(500);
    echo "Error: " . $e->getMessage();
}
?>
