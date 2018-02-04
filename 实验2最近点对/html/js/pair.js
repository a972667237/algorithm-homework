const MAX_DISTANCE = 99999;
var c = 1;
var linec = 1;
var minc = 10001;
var yc = 30001;
var mpc = 20001;
function Pair(x, y){
  this.x = x;
  this.y = y;
}
function Miner(p1, p2, d){
  this.p1 = p1;
  this.p2 = p2;
  this.d = d;
  this.c = mpc;
  mpc = mpc + 1;
  this.minItself = function()  {
    let p1 = this.p1;
    let p2 = this.p2;
    setTimeout(function(){
      line(p1, p2, this.c, "#9999cc");
    }, 500*c);
    c = c+1;
  }
  this.clean = function()  {
    setTimeout(function(){
      cleanLine(this.c);
    }, 500*c);
    c = c + 1;
  }
}
function makeArray(len){
  var arr = new Array();
  var w = $('.board').width();
  var h = $('.board').height();
  for(i = 0;i < len; i++){
    arr.push(new Pair(Math.floor(Math.random() * w), Math.floor(Math.random() * h)));
  }
  return arr;
}
function printPair(arr){
  var container = document.getElementsByClassName("board")[0];
  arr.forEach(function(v, i, a){
    container.innerHTML += makePair(v.x, v.y, i);
  });
}
function makePair(x, y, index=0){
 pointDiv = "<div style='left:" + x +
   "px;top:" + y + "px;' id='point" + index +"' class='point'></div>";
 return pointDiv;
}
function distance(p1, p2){
  return Math.sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
function dichotomy_pair(arr){
  var arrx = new Array();
  var arry = new Array();
  arrx = arr.slice(0);
  arry = arr.slice(0);
  arrx.sort(function(a, b){
    if(a.x == b.x)
      return a.y - b.y;
    return a.x - b.x;
  });
  arry.sort(function(a, b){
    if(a.y == b.y)
      return a.x - b.x;
    return a.y - b.y;
  });
  s = _dichotomy_pair(arrx, arry, 0, arr.length);
  return s;
}
function _dichotomy_pair(arrx, arry, l, r){
  if (l == r){
			return new Miner(new Pair(0, 0),new Pair(0, 0), MAX_DISTANCE);
  }
	if (l + 1 == r) {
		if (r >= arrx.length){
			return new Miner(new Pair(0, 0),new Pair(0, 0), MAX_DISTANCE);
    }
    setTimeout(function(){
      let d = linec;
      line(arrx[l], arrx[r], d, "red");
      linec = linec + 1;
      setTimeout(function(){
        cleanLine(d);
      }, 1000);
    }, 500*c);
    c = c+1;
		return new Miner(arrx[l], arrx[r], distance(arrx[l], arrx[r]));
	}
  let mid = parseInt((l + r) / 2);
  console.log("mid:" + mid);
  let midx = arrx[mid].x;
  let ly = new Array();
  let ry = new Array();
  arry.forEach(function(v, i, a){
    if(v.x <= midx)
      ly.push(v);
    else
      ry.push(v);
  });
  let x0 = minc;
  setTimeout(function(){
    printCarea(arrx[mid], x0);
  }, 500*c);
  minc = minc + 1;
  c = c + 1;
  let l_v = _dichotomy_pair(arrx, ly, l, mid);
  let r_v = _dichotomy_pair(arrx, ry, mid+1, r);
  setTimeout(function(){
    cleanLine(x0);
  }, 500*c);
  c = c + 1;
  let b = l_v.d<r_v.d;
  let d = b ? l_v : r_v;
  b?r_v.clean():l_v.clean();
  let x1 = minc;
  setTimeout(function(){
    printXarea(midx, d.d, x1);
  }, 500*c);
  minc = minc + 1;
  c = c + 1;
  tmp = new Array();
  arry.forEach(function(v, i, a){
    if(Math.abs(midx - v.x) < d.d)
      tmp.push(v);
  });
  tmp_len = tmp.length;
  min = d;
  min.minItself();
  for(i=0;i<tmp_len;i++){
    let p1 = tmp[i];
    let yyc = yc;
    yc = yc + 1;
    setTimeout(function(){
      printYarea(p1, d.d, yyc);
    }, 500*c);
    c = c + 1;
    for(j=i+1;j<tmp_len && Math.abs(p1.y - tmp[j].y)<d.d;j++){
      let p2 = tmp[j];
      tempd = distance(p1, p2);
      setTimeout(function(){
        let d = linec;
        line(p1, p2, d, "white");
        linec = linec + 1;
        setTimeout(function(){
          cleanLine(d);
        }, 1000);
      }, 500*c);
      c = c+1;
      if(tempd < min.d){
        min.clean();
        min = new Miner(p1, p2, tempd);
        min.minItself();
      }
    }
    setTimeout(function(){
      cleanLine(yyc);
    }, 500*c);
    c = c + 1;
  }
  setTimeout(function(){
    cleanLine(x1);
  }, 500*c);
  c = c +1;
  return min;
}
