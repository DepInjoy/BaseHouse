// 此脚本用于修改图表的参数

// 颜色分配
var colorRamp = ['#313695', '#4575b4', '#74add1', '#abd9e9', '#e0f3f8', '#ffffbf', '#fee090', '#fdae61', '#f46d43', '#d73027', '#a50026'];
var theOpac   = 1; // 透明度 0-1

// 地图相关
var theCenter = [121.49917602539062,31.197531659727318]; // 中心点坐标
var theZoom   = 4; //视角远近 数字
var theBear   = 180; // 地图旋转角度，正北为0，正东为90，正西为270，以此类推
var thePitch  = 30;   // 地图俯瞰角度，0为顶视图，60以上效果甚微

// mapStyle 与 mapAccessToken 另见说明

var mapStyle  = 'mapbox://styles/depinjoy/ck0ny7xc16upp1coct94021n9';
var mapAccessToken = 'pk.eyJ1IjoiZGVwaW5qb3kiLCJhIjoiY2swbnd6MDg2MDQ2eDNtbzB5bDA0d2xnayJ9.gc0OXmeA4WO3RfBAJIzkVQ';

// 点柱设置
var barSize   = 0.2; // 点柱大小
var barCorner = 0.5; // 点柱倒角，取值范围 0-1

// 光源设置
var theShadow = true; // 是否设置光源阴影
var theAlpha  = -40; // 光源高度
var theBeta   = 20; // 光源方向
