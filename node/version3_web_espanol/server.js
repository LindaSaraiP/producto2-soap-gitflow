const express = require('express');
const { numeroALetras } = require('./numero_es');
const app = express();
const PORT = 3000;
app.get('/', (req, res) => {
  const n = parseInt(req.query.n || '10', 10);
  res.type('text/plain').send(numeroALetras(n));
});
app.listen(PORT, () => console.log(`Servidor en http://localhost:${PORT}/?n=10`));
