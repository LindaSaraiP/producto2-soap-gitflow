var builder = WebApplication.CreateBuilder(args);
builder.WebHost.UseUrls("http://localhost:5000");
var app = builder.Build();

app.MapGet("/", (int? n) => Results.Text(NumeroALetras(n ?? 10), "text/plain; charset=utf-8"));
app.Run();

static string NumeroALetras(int n)
{
    if (n == 0) return "cero";
    if (n < 0) return "menos " + NumeroALetras(-n);
    if (n < 1000) return Centenas(n);
    if (n < 1000000)
    {
        int m = n / 1000, r = n % 1000;
        string pref = m == 1 ? "mil" : NumeroALetras(m) + " mil";
        return r > 0 ? pref + " " + Centenas(r) : pref;
    }
    int mill = n / 1000000, rem = n % 1000000;
    string pre = mill == 1 ? "un millon" : NumeroALetras(mill) + " millones";
    return rem > 0 ? pre + " " + NumeroALetras(rem) : pre;
}

static string Centenas(int n)
{
    string[] uni = ["cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"];
    var esp = new Dictionary<int,string>{{10,"diez"},{11,"once"},{12,"doce"},{13,"trece"},{14,"catorce"},{15,"quince"},{16,"dieciseis"},{17,"diecisiete"},{18,"dieciocho"},{19,"diecinueve"},{20,"veinte"},{21,"veintiuno"},{22,"veintidos"},{23,"veintitres"},{24,"veinticuatro"},{25,"veinticinco"},{26,"veintiseis"},{27,"veintisiete"},{28,"veintiocho"},{29,"veintinueve"}};
    var dec = new Dictionary<int,string>{{30,"treinta"},{40,"cuarenta"},{50,"cincuenta"},{60,"sesenta"},{70,"setenta"},{80,"ochenta"},{90,"noventa"}};
    var cie = new Dictionary<int,string>{{100,"cien"},{200,"doscientos"},{300,"trescientos"},{400,"cuatrocientos"},{500,"quinientos"},{600,"seiscientos"},{700,"setecientos"},{800,"ochocientos"},{900,"novecientos"}};
    if(n<10) return uni[n]; if(esp.ContainsKey(n)) return esp[n];
    if(n<100){int d=n/10*10,u=n%10; return u>0 ? dec[d]+" y "+uni[u] : dec[d];}
    if(cie.ContainsKey(n)) return cie[n]; int c=n/100*100,r=n%100; return (c==100?"ciento":cie[c])+" "+Centenas(r);
}
