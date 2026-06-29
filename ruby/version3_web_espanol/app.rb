require 'webrick'

def unidades(n); %w[cero uno dos tres cuatro cinco seis siete ocho nueve][n]; end

def centenas(n)
  esp={10=>'diez',11=>'once',12=>'doce',13=>'trece',14=>'catorce',15=>'quince',16=>'dieciseis',17=>'diecisiete',18=>'dieciocho',19=>'diecinueve',20=>'veinte',21=>'veintiuno',22=>'veintidos',23=>'veintitres',24=>'veinticuatro',25=>'veinticinco',26=>'veintiseis',27=>'veintisiete',28=>'veintiocho',29=>'veintinueve'}
  dec={30=>'treinta',40=>'cuarenta',50=>'cincuenta',60=>'sesenta',70=>'setenta',80=>'ochenta',90=>'noventa'}
  cie={100=>'cien',200=>'doscientos',300=>'trescientos',400=>'cuatrocientos',500=>'quinientos',600=>'seiscientos',700=>'setecientos',800=>'ochocientos',900=>'novecientos'}
  return unidades(n) if n < 10; return esp[n] if esp[n]
  return n % 10 > 0 ? "#{dec[n/10*10]} y #{unidades(n%10)}" : dec[n] if n < 100
  return cie[n] if cie[n]
  c=n/100*100; r=n%100; "#{c==100 ? 'ciento' : cie[c]} #{centenas(r)}"
end

def numero(n)
  return 'cero' if n == 0; return 'menos ' + numero(-n) if n < 0; return centenas(n) if n < 1000
  if n < 1_000_000
    m=n/1000; r=n%1000; pref=m==1 ? 'mil' : "#{numero(m)} mil"; return r>0 ? "#{pref} #{centenas(r)}" : pref
  end
  m=n/1_000_000; r=n%1_000_000; pref=m==1 ? 'un millon' : "#{numero(m)} millones"; r>0 ? "#{pref} #{numero(r)}" : pref
end

server = WEBrick::HTTPServer.new(Port: 3000)
server.mount_proc('/') { |req,res| res['Content-Type']='text/plain; charset=utf-8'; res.body=numero((req.query['n'] || '10').to_i) }
trap('INT') { server.shutdown }
puts 'Servidor en http://localhost:3000/?n=10'
server.start
