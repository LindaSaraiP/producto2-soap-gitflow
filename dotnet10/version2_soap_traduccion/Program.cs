using System.Text;
using System.Text.RegularExpressions;

var builder = WebApplication.CreateBuilder(args);
builder.WebHost.UseUrls("http://localhost:5000");
var app = builder.Build();

app.MapGet("/", async (int? n) =>
{
    string english = await NumberToWordsAsync(n ?? 10);
    return Results.Text(Translator.ToSpanish(english), "text/plain; charset=utf-8");
});

app.Run();

static async Task<string> NumberToWordsAsync(int n)
{
    string body = $"""
    <?xml version="1.0" encoding="utf-8"?>
    <soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
      <soap:Body><NumberToWords xmlns="http://www.dataaccess.com/webservicesserver/"><ubiNum>{n}</ubiNum></NumberToWords></soap:Body>
    </soap:Envelope>
    """;
    using var client = new HttpClient();
    var request = new HttpRequestMessage(HttpMethod.Post, "https://www.dataaccess.com/webservicesserver/NumberConversion.wso");
    request.Content = new StringContent(body, Encoding.UTF8, "text/xml");
    request.Headers.Add("SOAPAction", "http://www.dataaccess.com/webservicesserver/NumberToWords");
    string xml = await (await client.SendAsync(request)).Content.ReadAsStringAsync();
    var match = Regex.Match(xml, @"<m:NumberToWordsResult>(.*?)</m:NumberToWordsResult>|<NumberToWordsResult>(.*?)</NumberToWordsResult>");
    return match.Success ? (match.Groups[1].Value != "" ? match.Groups[1].Value : match.Groups[2].Value).Trim() : xml;
}
