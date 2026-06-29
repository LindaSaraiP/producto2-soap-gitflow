# Producto 2 - Cliente SOAP Multilenguaje

Repositorio para el caso de estudio **Cliente SOAP** basado en la clase del lunes 15/06/2026.

El objetivo es implementar, en varios lenguajes de programación del lado del servidor, tres versiones de una aplicación que trabaja con números:

1. Consumir el servicio web SOAP público `NumberConversion` y mostrar el número en letras en inglés.
2. Consumir el mismo servicio SOAP y traducir el resultado de inglés a español mediante una librería/módulo de traducción incluido en cada lenguaje.
3. Implementar una aplicación web propia que convierta un número recibido por URL a letras en español.

Servicio SOAP utilizado:

```text
https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL
```

## Lenguajes incluidos

- PHP
- Node.js
- C# / .NET 10
- Golang
- Java
- C++
- Ruby
- Perl
- Rust

## Estructura

```text
producto2-soap-multilenguaje/
├── php/
├── node/
├── dotnet10/
├── golang/
├── java/
├── cpp/
├── ruby/
├── perl/
├── rust/
└── docs/
```

Cada lenguaje contiene:

```text
version1_soap/
version2_soap_traduccion/
version3_web_espanol/
```

## Recomendación de Git Flow / GitHub Flow

Ramas sugeridas:

```text
main
develop
feature/php
feature/node
feature/dotnet10
feature/golang
feature/java
feature/cpp
feature/ruby
feature/perl
feature/rust
```

Flujo sugerido:

1. Crear la rama `develop` desde `main`.
2. Crear una rama `feature` por lenguaje.
3. Hacer commits por avance.
4. Abrir Pull Request de cada `feature` hacia `develop`.
5. Al finalizar todo, abrir Pull Request de `develop` hacia `main`.

## Nota sobre traducción

La versión 2 de cada lenguaje incluye una pequeña librería o módulo local de traducción de palabras comunes que devuelve el servicio SOAP. Esto evita depender de APIs externas de traducción y permite que el proyecto sea más fácil de ejecutar en clase.

## Nota sobre números soportados

La conversión local a español de la versión 3 está pensada para enteros no negativos en un rango común de demostración. Para probar se recomienda usar valores como `10`, `25`, `100`, `215`, `1000` o `2026`.
