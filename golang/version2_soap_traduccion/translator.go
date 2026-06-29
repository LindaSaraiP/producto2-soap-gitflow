package main

import "strings"

func translateToSpanish(text string) string {
    dict := map[string]string{"zero":"cero","one":"uno","two":"dos","three":"tres","four":"cuatro","five":"cinco","six":"seis","seven":"siete","eight":"ocho","nine":"nueve","ten":"diez","eleven":"once","twelve":"doce","thirteen":"trece","fourteen":"catorce","fifteen":"quince","sixteen":"dieciseis","seventeen":"diecisiete","eighteen":"dieciocho","nineteen":"diecinueve","twenty":"veinte","thirty":"treinta","forty":"cuarenta","fifty":"cincuenta","sixty":"sesenta","seventy":"setenta","eighty":"ochenta","ninety":"noventa","hundred":"cien","thousand":"mil","million":"millon","millions":"millones","and":"y"}
    text = strings.ToLower(text)
    for en, es := range dict { text = strings.ReplaceAll(text, en, es) }
    return strings.TrimSpace(text)
}
