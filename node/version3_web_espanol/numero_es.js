function unidades(n){return ['cero','uno','dos','tres','cuatro','cinco','seis','siete','ocho','nueve'][n];}
function centenas(n){
  const especiales={10:'diez',11:'once',12:'doce',13:'trece',14:'catorce',15:'quince',16:'dieciseis',17:'diecisiete',18:'dieciocho',19:'diecinueve',20:'veinte',21:'veintiuno',22:'veintidos',23:'veintitres',24:'veinticuatro',25:'veinticinco',26:'veintiseis',27:'veintisiete',28:'veintiocho',29:'veintinueve'};
  const decenas={30:'treinta',40:'cuarenta',50:'cincuenta',60:'sesenta',70:'setenta',80:'ochenta',90:'noventa'};
  const cienes={100:'cien',200:'doscientos',300:'trescientos',400:'cuatrocientos',500:'quinientos',600:'seiscientos',700:'setecientos',800:'ochocientos',900:'novecientos'};
  if(n<10)return unidades(n); if(especiales[n])return especiales[n]; if(n<100){let d=Math.floor(n/10)*10,u=n%10;return u?`${decenas[d]} y ${unidades(u)}`:decenas[d];}
  if(cienes[n])return cienes[n]; let c=Math.floor(n/100)*100,r=n%100; return `${c===100?'ciento':cienes[c]} ${centenas(r)}`;
}
function numeroALetras(n){
  n=parseInt(n,10); if(isNaN(n)) return 'numero invalido'; if(n===0)return 'cero'; if(n<0)return 'menos '+numeroALetras(-n); if(n<1000)return centenas(n);
  if(n<1000000){let m=Math.floor(n/1000),r=n%1000; let pref=m===1?'mil':`${numeroALetras(m)} mil`; return r?`${pref} ${centenas(r)}`:pref;}
  let mill=Math.floor(n/1000000),r=n%1000000; let pref=mill===1?'un millon':`${numeroALetras(mill)} millones`; return r?`${pref} ${numeroALetras(r)}`:pref;
}
module.exports={numeroALetras};
