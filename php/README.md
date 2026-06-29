# PHP

Antes de ejecutar, habilitar extensiones en `php.ini`:

```ini
extension=soap
extension=zip
extension=intl
```

## Versión 1

```bash
cd php/version1_soap
php -S localhost:8000
```

Abrir:

```text
http://localhost:8000/clisoap1.php?n=10
```

## Versión 2

```bash
cd php/version2_soap_traduccion
composer install
php -S localhost:8000
```

Abrir:

```text
http://localhost:8000/clisoap2.php?n=10
```

## Versión 3

```bash
cd php/version3_web_espanol
php -S localhost:8000
```

Abrir:

```text
http://localhost:8000/conintl.php?n=10
```
