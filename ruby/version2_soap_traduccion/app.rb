require 'webrick'
require 'net/http'
require 'uri'

def number_to_words(n)
  uri = URI('https://www.dataaccess.com/webservicesserver/NumberConversion.wso')
  body = "<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"><soap:Body><NumberToWords xmlns=\"http://www.dataaccess.com/webservicesserver/\"><ubiNum>#{n}</ubiNum></NumberToWords></soap:Body></soap:Envelope>"
  req = Net::HTTP::Post.new(uri); req['Content-Type']='text/xml; charset=utf-8'; req['SOAPAction']='http://www.dataaccess.com/webservicesserver/NumberToWords'; req.body=body
  xml = Net::HTTP.start(uri.hostname, uri.port, use_ssl: true) { |http| http.request(req) }.body
  match = xml.match(/<m:NumberToWordsResult>(.*?)<\/m:NumberToWordsResult>|<NumberToWordsResult>(.*?)<\/NumberToWordsResult>/)
  match ? (match[1] || match[2]).strip : xml
end

def translate(text)
  dict = {'zero'=>'cero','one'=>'uno','two'=>'dos','three'=>'tres','four'=>'cuatro','five'=>'cinco','six'=>'seis','seven'=>'siete','eight'=>'ocho','nine'=>'nueve','ten'=>'diez','eleven'=>'once','twelve'=>'doce','thirteen'=>'trece','fourteen'=>'catorce','fifteen'=>'quince','sixteen'=>'dieciseis','seventeen'=>'diecisiete','eighteen'=>'dieciocho','nineteen'=>'diecinueve','twenty'=>'veinte','thirty'=>'treinta','forty'=>'cuarenta','fifty'=>'cincuenta','sixty'=>'sesenta','seventy'=>'setenta','eighty'=>'ochenta','ninety'=>'noventa','hundred'=>'cien','thousand'=>'mil','million'=>'millon','millions'=>'millones','and'=>'y'}
  result = text.downcase
  dict.each { |en, es| result = result.gsub(en, es) }
  result.strip
end

server = WEBrick::HTTPServer.new(Port: 3000)
server.mount_proc('/') { |req,res| res['Content-Type']='text/plain; charset=utf-8'; res.body=translate(number_to_words(req.query['n'] || '10')) }
trap('INT') { server.shutdown }
puts 'Servidor en http://localhost:3000/?n=10'
server.start
