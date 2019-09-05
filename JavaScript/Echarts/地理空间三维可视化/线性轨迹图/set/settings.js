// 此脚本用于修改图表的参数

// 路线属性
var colorOrWidth  = 3 ; // 0代表既不用色彩也不用宽度来表示值，1代表用色彩，2代表用宽度，3代表二者皆用
var theColorRamp  = ['#313695', '#4575b4', '#74add1', '#abd9e9', '#e0f3f8', '#ffffbf', '#fee090', '#fdae61', '#f46d43', '#d73027']; // 路线颜色
var theWidthRatio = 0.2 // 宽度与值的比值

// 固定属性，当该属性没有和值相关，会自动设成如下值
var theColor  = 'rgb(200, 35, 45)'; // 线的颜色
var theWidth  = 2;    // 线的宽度
var theOpac   = 0.3;  // 线的透明度

// 地图相关
var theCenter = [114.270192,30.608165]; // 中心点坐标
var theZoom   = 12; //视角远近 数字

// 动画效果
var effectShow  = true;// 是否展示动画
var theSpeed    = 0;   // 尾迹速度，当尾迹速度不等于 0 时，使用单次循环时间作为速度依据
var thePeriod   = 6;   // 单次循环时间，只有当尾迹速度为 0 时才能生效
var theEffWidth = 8;   // 尾迹宽度
var theEffLength= 0.3; // 尾迹长度

// 百度地图
// 百度地图的accesstoken需要到 html 的第18行 自行进行替换
var mapStyle= [{
    "featureType": "estatelabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#8d694eff"
    }
}, {
    "featureType": "restaurantlabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "restaurantlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "lifeservicelabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "lifeservicelabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "transportationlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "transportationlabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "on"
    }
}, {
    "featureType": "financelabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "financelabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "land",
    "elementType": "geometry",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "building",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#e7dfd6ff"
    }
}, {
    "featureType": "building",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#b9a797ff"
    }
}, {
    "featureType": "estatelabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ebe1d8ff"
    }
}, {
    "featureType": "estatelabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "estatelabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "28"
    }
}, {
    "featureType": "manmade",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff"
    }
}, {
    "featureType": "manmade",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "manmade",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "36"
    }
}, {
    "featureType": "manmade",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#b6997fff"
    }
}, {
    "featureType": "green",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "education",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "medical",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "scenicspots",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "entertainment",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "estate",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "shopping",
    "elementType": "geometry",
    "stylers": {
        "visibility": "on",
        "color": "#ecececff"
    }
}, {
    "featureType": "transportation",
    "elementType": "geometry",
    "stylers": {
        "color": "#ecececff"
    }
}, {
    "featureType": "transportation",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff"
    }
}, {
    "featureType": "transportation",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#b6997fff"
    }
}, {
    "featureType": "transportation",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "36"
    }
}, {
    "featureType": "medical",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff"
    }
}, {
    "featureType": "medical",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#b6997fff"
    }
}, {
    "featureType": "medical",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "36"
    }
}, {
    "featureType": "education",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff"
    }
}, {
    "featureType": "education",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#b6997fff"
    }
}, {
    "featureType": "education",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "36"
    }
}, {
    "featureType": "carservicelabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "carservicelabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "shoppinglabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "hotellabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "governmentlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "companylabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "businesstowerlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "entertainmentlabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "entertainmentlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "medicallabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "educationlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "airportlabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "airportlabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "36"
    }
}, {
    "featureType": "airportlabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff"
    }
}, {
    "featureType": "airportlabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#b6997fff"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "28"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#4a4a4aff"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "educationlabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#8d694eff"
    }
}, {
    "featureType": "educationlabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ebe1d8ff"
    }
}, {
    "featureType": "educationlabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "26"
    }
}, {
    "featureType": "medicallabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#8d694eff"
    }
}, {
    "featureType": "medicallabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ebe1d8ff"
    }
}, {
    "featureType": "medicallabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "24"
    }
}, {
    "featureType": "businesstowerlabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ebe1d8ff"
    }
}, {
    "featureType": "businesstowerlabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#8d694eff"
    }
}, {
    "featureType": "businesstowerlabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "24"
    }
}, {
    "featureType": "companylabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "hotellabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#8d694eff"
    }
}, {
    "featureType": "hotellabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ebe1d8ff"
    }
}, {
    "featureType": "hotellabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "24"
    }
}, {
    "featureType": "shoppinglabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#8d694eff"
    }
}, {
    "featureType": "shoppinglabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ebe1d8ff"
    }
}, {
    "featureType": "transportationlabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#4a4a4aff"
    }
}, {
    "featureType": "transportationlabel",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "24"
    }
}, {
    "featureType": "scenicspots",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff"
    }
}, {
    "featureType": "scenicspots",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#b6997fff"
    }
}, {
    "featureType": "scenicspots",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "36"
    }
}, {
    "featureType": "governmentlabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#4a4a4aff"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "district",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "district",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#72533aff",
        "weight": "3.5"
    }
}, {
    "featureType": "town",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#72533aff",
        "weight": "3"
    }
}, {
    "featureType": "town",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "village",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff",
        "weight": "2.5"
    }
}, {
    "featureType": "village",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#72533aff",
        "weight": "40"
    }
}, {
    "featureType": "village",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": "20"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#fdf0daff"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#ffd993ff"
    }
}, {
    "featureType": "highway",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#000000ff"
    }
}, {
    "featureType": "highway",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#fdf0daff"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#ffd993ff"
    }
}, {
    "featureType": "nationalway",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#000000ff"
    }
}, {
    "featureType": "nationalway",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "provincialway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#ffd993ff"
    }
}, {
    "featureType": "provincialway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#fdf0daff"
    }
}, {
    "featureType": "provincialway",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#000000ff"
    }
}, {
    "featureType": "provincialway",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "subway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#f5a117ff"
    }
}, {
    "featureType": "manmade",
    "elementType": "labels",
    "stylers": {
        "visibility": "on"
    }
}]