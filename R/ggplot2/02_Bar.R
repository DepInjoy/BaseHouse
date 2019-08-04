library(grid)

#设置基本映射关系
p <- ggplot(mtcars)

p0 <- p + geom_bar(stat= 'identity') +
    aes(x = factor(carb), y = wt) +
    labs(title="Bar 1")

p1 <- p + geom_bar(aes(x = factor(carb))) +
    coord_flip() +                            # 坐标轴翻转
    labs(title="Bar 2")

p2 <- p + geom_bar(aes(x = factor(1),
    fill=factor(gear))) +
    coord_polar() +                         #极坐标转换
    labs(title="风玫瑰图(windrose) 1")

p3 <- p + geom_bar(aes(x = factor(carb),
    fill=factor(gear))) +                  #标注的颜色属性
    coord_polar() +
    labs(title="风玫瑰图(windrose) 2")

grid.newpage()
pushViewport(viewport(layout = grid.layout(2,2)))
vplayout <- function(x,y){
  viewport(layout.pos.row = x, layout.pos.col = y)
}

print(p0, vp = vplayout(1,1))
print(p1, vp = vplayout(1,2))
print(p2, vp = vplayout(2,1))
print(p3, vp = vplayout(2,2))

p3 + facet_grid(.~carb, scales = 'free')