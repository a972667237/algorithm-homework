var site = {
  width: 60,
  height: 60
}
var callTime = 1;
const spaceTime = 100;
function redIt(id){
  let call = callTime;
  callTime++;
  setTimeout(function(){
    let s = $("#site_" + id);
    s.css("background-color", "red");
  }, call * spaceTime);
}
function whiteIt(id){
  let call = callTime;
  callTime++;
  setTimeout(function(){
    let s = $("#site_" + id);
    s.css("background-color", "white");
  }, call * spaceTime);
}
function goldIt(){
  let call = callTime;
  callTime++;
  setTimeout(function(){
    let s = $(".site");
    s.each(function(i, e){
      if($(e).css("background-color") == "rgb(255, 0, 0)")
        $(e).css("background-color", "#FFD700");
    });
  }, call * spaceTime);
}
function readbackIt(){
  let call = callTime;
  callTime++;
  setTimeout(function(){
    let s = $(".site");
    s.each(function(i, e){
      if($(e).css("background-color") == "rgb(255, 215, 0)")
        $(e).css("background-color", "red");
    });
  }, call * spaceTime);
}
function createViewer(n){
  let $p = $(".draw_place");
  $p.width(n*site.width);
  for(let i=1;i<n+1;i++){
    let row_info = "<div class='row' id='row_"+ i +"'>"
    for(let j=1;j<n+1;j++){
      let site_info = "<div class='site' id='site_"+ ((i-1)*n + j) + "'></div>";
      row_info+= site_info;
    }
    row_info += "</div>";
    $p.html($p.html() + row_info);
  }
}
function doItCut(c, len){
	let isFail = false;
	let last, now;
	if (len > 1) {
		last = len - 1;
		now = c[last];
	}
	else {
		isFail = false;
	}
	for (let i = 0; (i < len - 1) && (!isFail); i++) {
		if (now - c[i] == last - i || now - c[i] == i - last || now == c[i])
			isFail = true;
	}
	return !isFail;
}
function queue_cut(n) {
		count = 0;
		let each = new Array();
		let now = 0;
		let end = n - 1;
		each[0] = 0;
    redIt(1);
		let canContinue = true;
		while (canContinue) {
			if (!doItCut(each, now+1)) {  // 大概率事件放if中
				while (each[now] == end) {
          whiteIt(now*n + each[now] + 1);
					each[now] = 0;
					now--;
					if (now == -1) {
						canContinue = false;
						break;
					}
				}
				if (!canContinue)
					break;
        whiteIt(now*n + each[now] + 1);
				each[now]++;
        redIt(now*n + each[now] + 1);
			}
			else {
				if (now != end) {
					now++;
					each[now] = 0;
          redIt(now*n + each[now] + 1);
				}
				else {
					/*int *save = new int[n];
					for (int i = 0; i < n; i++)
					save[i] = each[i];
					suitableResult.push_back(save);*/
					count++;
          goldIt();
          goldIt();
          goldIt();
          goldIt();
          goldIt();
          goldIt();
          readbackIt();
          whiteIt(now*n + each[now] + 1);
					while (each[now] == end) {
            whiteIt(now*n + each[now] + 1);
						each[now] = 0;
						now--;
					}
					each[now]++;
          redIt(now*n + each[now] + 1);
				}
			}
		}
    console.log(count);
	}
