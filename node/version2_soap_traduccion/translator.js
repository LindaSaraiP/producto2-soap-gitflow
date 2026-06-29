const dictionary = {
  'zero':'cero','one':'uno','two':'dos','three':'tres','four':'cuatro','five':'cinco','six':'seis','seven':'siete','eight':'ocho','nine':'nueve','ten':'diez','eleven':'once','twelve':'doce','thirteen':'trece','fourteen':'catorce','fifteen':'quince','sixteen':'dieciseis','seventeen':'diecisiete','eighteen':'dieciocho','nineteen':'diecinueve','twenty':'veinte','thirty':'treinta','forty':'cuarenta','fifty':'cincuenta','sixty':'sesenta','seventy':'setenta','eighty':'ochenta','ninety':'noventa','hundred':'cien','thousand':'mil','million':'millon','millions':'millones','and':'y'
};
function translateToSpanish(text) {
  return text.toLowerCase().split(/([\s-]+)/).map(part => dictionary[part] || part).join('').replace(/\s+/g, ' ').trim();
}
module.exports = { translateToSpanish };
