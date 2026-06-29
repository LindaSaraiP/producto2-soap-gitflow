require 'webrick'
require 'net/http'
require 'uri'

server = WEBrick::HTTPServer.new(Port: 3000)

def number_to_words(n)
  uri = URI('https://www.dataaccess.com/webservicesserver/NumberConversion.wso')
  body = "<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"><soap:Body><NumberToWords xmlns=\"http://www.dataaccess.com/webservicesserver/\"><ubiNum>#{n}</ubiNum></NumberToWords></soap:Body></soap:Envelope>"
  req = Net::HTTP::Post.new(uri)
  req['Content-Type'] = 'text/xml; charset=utf-8'
  req['SOAPAction'] = 'http://www.dataaccess.com/webservicesserver/NumberToWords'
  req.body = body
  res = Net::HTTP.start(uri.hostname, uri.port, use_ssl: true) { |http| http.request(req) }
  xml = res.body
  match = xml.match(/<m:NumberToWordsResult>(.*?)<\/m:NumberToWordsResult>|<NumberToWordsResult>(.*?)<\/NumberToWordsResult>/)
  match ? (match[1] || match[2]).strip : xml
end

server.mount_proc('/') do |req, res|
  n = req.query['n'] || '10'
  res['Content-Type'] = 'text/plain; charset=utf-8'
  res.body = number_to_words(n)
end
trap('INT') { server.shutdown }
puts 'Servidor en http://localhost:3000/?n=10'
server.start
