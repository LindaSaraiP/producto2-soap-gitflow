const express = require('express');
const app = express();
const PORT = 3000;

async function numberToWords(n) {
  const body = `<?xml version="1.0" encoding="utf-8"?>
  <soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
    <soap:Body>
      <NumberToWords xmlns="http://www.dataaccess.com/webservicesserver/">
        <ubiNum>${n}</ubiNum>
      </NumberToWords>
    </soap:Body>
  </soap:Envelope>`;

  const response = await fetch('https://www.dataaccess.com/webservicesserver/NumberConversion.wso', {
    method: 'POST',
    headers: {
      'Content-Type': 'text/xml; charset=utf-8',
      'SOAPAction': 'http://www.dataaccess.com/webservicesserver/NumberToWords'
    },
    body
  });

  const xml = await response.text();
  const match = xml.match(/<m:NumberToWordsResult>(.*?)<\/m:NumberToWordsResult>/) || xml.match(/<NumberToWordsResult>(.*?)<\/NumberToWordsResult>/);
  return match ? match[1].trim() : xml;
}

app.get('/', async (req, res) => {
  try {
    const n = parseInt(req.query.n || '10', 10);
    const result = await numberToWords(n);
    res.type('text/plain').send(result);
  } catch (error) {
    res.status(500).send('Error SOAP: ' + error.message);
  }
});

app.listen(PORT, () => console.log(`Servidor en http://localhost:${PORT}/?n=10`));
