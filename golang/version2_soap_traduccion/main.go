package main

import (
    "bytes"
    "fmt"
    "io"
    "net/http"
    "regexp"
)

func numberToWords(n string) (string, error) {
    body := fmt.Sprintf(`<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/"><soap:Body><NumberToWords xmlns="http://www.dataaccess.com/webservicesserver/"><ubiNum>%s</ubiNum></NumberToWords></soap:Body></soap:Envelope>`, n)
    req, _ := http.NewRequest("POST", "https://www.dataaccess.com/webservicesserver/NumberConversion.wso", bytes.NewBufferString(body))
    req.Header.Set("Content-Type", "text/xml; charset=utf-8")
    req.Header.Set("SOAPAction", "http://www.dataaccess.com/webservicesserver/NumberToWords")
    resp, err := http.DefaultClient.Do(req)
    if err != nil { return "", err }
    defer resp.Body.Close()
    data, _ := io.ReadAll(resp.Body)
    re := regexp.MustCompile(`<m:NumberToWordsResult>(.*?)</m:NumberToWordsResult>|<NumberToWordsResult>(.*?)</NumberToWordsResult>`)
    match := re.FindStringSubmatch(string(data))
    if len(match) > 1 { if match[1] != "" { return match[1], nil }; return match[2], nil }
    return string(data), nil
}

func main() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        n := r.URL.Query().Get("n"); if n == "" { n = "10" }
        english, err := numberToWords(n)
        if err != nil { http.Error(w, err.Error(), 500); return }
        fmt.Fprint(w, translateToSpanish(english))
    })
    fmt.Println("Servidor en http://localhost:3000/?n=10")
    http.ListenAndServe(":3000", nil)
}
