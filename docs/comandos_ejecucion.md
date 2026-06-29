# Comandos de ejecución

Todos los ejemplos reciben el número desde la URL con el parámetro `n`.

Ejemplo general:

```text
http://localhost:3000/?n=10
```

En PHP se usa el puerto `8000`, igual que en la clase:

```text
http://localhost:8000/clisoap1.php?n=10
http://localhost:8000/clisoap2.php?n=10
http://localhost:8000/conintl.php?n=10
```

## PHP

```bash
cd php/version1_soap
php -S localhost:8000
```

```bash
cd php/version2_soap_traduccion
composer install
php -S localhost:8000
```

```bash
cd php/version3_web_espanol
php -S localhost:8000
```

## Node.js

```bash
cd node/version1_soap
npm install
npm start
```

```bash
cd node/version2_soap_traduccion
npm install
npm start
```

```bash
cd node/version3_web_espanol
npm install
npm start
```

## C# / .NET 10

```bash
cd dotnet10/version1_soap
dotnet run
```

```bash
cd dotnet10/version2_soap_traduccion
dotnet run
```

```bash
cd dotnet10/version3_web_espanol
dotnet run
```

## Golang

```bash
cd golang/version1_soap
go run main.go
```

```bash
cd golang/version2_soap_traduccion
go run .
```

```bash
cd golang/version3_web_espanol
go run main.go
```

## Java

```bash
cd java/version1_soap
javac Main.java
java Main
```

```bash
cd java/version2_soap_traduccion
javac Main.java
java Main
```

```bash
cd java/version3_web_espanol
javac Main.java
java Main
```

## C++

```bash
cd cpp/version1_soap
g++ main.cpp -o app
./app
```

```bash
cd cpp/version2_soap_traduccion
g++ main.cpp -o app
./app
```

```bash
cd cpp/version3_web_espanol
g++ main.cpp -o app
./app
```

En Windows puede ejecutarse como:

```bash
g++ main.cpp -o app.exe
app.exe
```

## Ruby

```bash
cd ruby/version1_soap
ruby app.rb
```

```bash
cd ruby/version2_soap_traduccion
ruby app.rb
```

```bash
cd ruby/version3_web_espanol
ruby app.rb
```

## Perl

```bash
cd perl/version1_soap
perl app.pl
```

```bash
cd perl/version2_soap_traduccion
perl app.pl
```

```bash
cd perl/version3_web_espanol
perl app.pl
```

## Rust

```bash
cd rust/version1_soap
cargo run
```

```bash
cd rust/version2_soap_traduccion
cargo run
```

```bash
cd rust/version3_web_espanol
cargo run
```
