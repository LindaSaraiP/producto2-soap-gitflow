<?php
// Ejecutar:
// php -S localhost:8000
// http://localhost:8000/clisoap1.php?n=10

header('Content-Type: text/plain; charset=utf-8');

$n = isset($_GET['n']) ? intval($_GET['n']) : 10;
$wsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL";

try {
    $cliente = new SoapClient($wsdl);
    $respuesta = $cliente->NumberToWords(array("ubiNum" => $n));
    echo trim($respuesta->NumberToWordsResult);
} catch (Exception $e) {
    http_response_code(500);
    echo "Error SOAP: " . $e->getMessage();
}
?>
