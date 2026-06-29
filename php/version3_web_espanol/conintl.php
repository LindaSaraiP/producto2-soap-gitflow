<?php
// Ejecutar:
// php -S localhost:8000
// http://localhost:8000/conintl.php?n=10

header('Content-Type: text/plain; charset=utf-8');

$n = isset($_GET['n']) ? intval($_GET['n']) : 10;
$formateador = new NumberFormatter("es", NumberFormatter::SPELLOUT);
echo $formateador->format($n);
?>
