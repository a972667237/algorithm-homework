const colors = ["#467500", "#0000c6", "#28FF28", "#FFF", "#9999cc"];
function Pair(x, y){
  this.x = x;
  this.y = y;
}
function line(p1, p2, index, color="red"){
  console.log(p1);
  console.log(p2);
 var slope; //斜率
 var direction;//坐标运动方向
 var tx = p2.x - p1.x;
 var ty = p2.y - p1.y;
 if(tx == 0 && ty == 0)return;
 var points = "";
 var axis;//坐标轴上的坐标
 if(Math.abs(tx) >= Math.abs(ty)){//在x轴上移动
   direction = tx > 0 ? 1 : -1;
   tx = Math.abs(tx);
   slope = ty / tx;
   axis = p1.x;
   for(i = 0; i < tx; i ++){
     points += makedot(axis, p1.y + i * slope, index, color);
     axis += direction;
   }

 }else{//在y轴上移动
   direction = ty > 0 ? 1 : -1;
   ty = Math.abs(ty);
   slope = tx / ty;
   axis = p1.y;
   for(i = 0; i < ty; i ++){
     points += makedot(p1.x + i * slope, axis,  index, color);
     axis += direction;
   }
 }
 let container = document.getElementsByClassName("board")[0];
 container.innerHTML += points;
}
function makedot(x, y, index, color = "#fff"){
  x = x + 2.5;
  y = y + 2.5;
 pointDiv = "<div style='height:1px;position:absolute;left:" + x +
   "px;top:" + y + "px;width:1px;background:"+ color +";overflow:hidden' class='line" + index +"'></div>";
 return pointDiv;
}
function cleanLine(index=0){
  console.log("clean" + index);
  $(".line" + index).remove();
}
function printXarea(midx, d, index, color=colors[4]){
  if(d>10000)
    return;
  let h = $(".board").height();
  line(new Pair(midx-d, 0), new Pair(midx-d, h), index, color);
  line(new Pair(midx+d, 0), new Pair(midx+d, h), index, color);
}
function printYarea(p, d, index, color=colors[1]){
  line(new Pair(p.x-d, p.y-d), new Pair(p.x+d, p.y-d), index, color);
  line(new Pair(p.x-d, p.y+d), new Pair(p.x+d, p.y+d), index, color);
}
function printCarea(p, index, color=colors[2]){
  let h = $(".board").height();
  line(new Pair(p.x, 0), new Pair(p.x, h), index, color);
}
