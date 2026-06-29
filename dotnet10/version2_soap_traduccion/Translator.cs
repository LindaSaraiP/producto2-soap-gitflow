public static class Translator
{
    private static readonly Dictionary<string, string> Dict = new()
    {
        ["zero"]="cero", ["one"]="uno", ["two"]="dos", ["three"]="tres", ["four"]="cuatro",
        ["five"]="cinco", ["six"]="seis", ["seven"]="siete", ["eight"]="ocho", ["nine"]="nueve",
        ["ten"]="diez", ["eleven"]="once", ["twelve"]="doce", ["thirteen"]="trece", ["fourteen"]="catorce",
        ["fifteen"]="quince", ["sixteen"]="dieciseis", ["seventeen"]="diecisiete", ["eighteen"]="dieciocho", ["nineteen"]="diecinueve",
        ["twenty"]="veinte", ["thirty"]="treinta", ["forty"]="cuarenta", ["fifty"]="cincuenta", ["sixty"]="sesenta",
        ["seventy"]="setenta", ["eighty"]="ochenta", ["ninety"]="noventa", ["hundred"]="cien", ["thousand"]="mil",
        ["million"]="millon", ["millions"]="millones", ["and"]="y"
    };
    public static string ToSpanish(string text)
    {
        var result = text.ToLowerInvariant();
        foreach (var item in Dict) result = result.Replace(item.Key, item.Value);
        return result.Trim();
    }
}
