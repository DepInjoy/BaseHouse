#通过ggplot2的aes()函数设定默认映射关系
p <- ggplot(mtcars, aes(x = mpg, y = wt))


#采用默认的映射关系绘制散点图
p0 <- p + geom_point() + labs(title="图1")

#添加图层的shape映射关系
p1 <- p + geom_point(aes(shape = factor(carb))) + labs(title="图2")

#修改默认的y的映射关系, 注意图中y轴名称仍然以默认的wt表示
p2 <- p + geom_point(aes(y = carb)) + labs(title="图3", y="carb")

#重新定义point几何对象中的数据与映射关系
df <- mtcars[which(mtcars$am==1),]
p3 <- p + geom_point(data = df,aes(x = mpg, y = wt)) + labs(title="图4")




p4 <- p + geom_point(aes(color=factor(gear))) + 
  labs(title="图5") +
  theme(plot.title = element_text(size = rel(2)) ,
        plot.background = element_rect(fill = "#0C2240", colour = "grey50"));

p5 <- p + geom_point(aes(color=gear)) + labs(title="图6")

p <- ggplot(mtcars, aes(x = mpg, y = wt,color = factor(gear)))
p6 <- p + geom_point(aes(shape=factor(cyl))) + labs(title="图7")

mt <- ggplot(mtcars, aes(mpg, wt, colour = factor(cyl))) +  geom_point()
p7 <- mt + facet_grid(. ~ cyl, scales = "free")

#新建页面,并划分为2*2矩阵
grid.newpage()
pushViewport(viewport(layout = grid.layout(2,4)))
vplayout <- function(x,y){
  viewport(layout.pos.row = x, layout.pos.col = y)
}

print(p0, vp = vplayout(1,1))
print(p1, vp = vplayout(1,2))
print(p2, vp = vplayout(1,3))
print(p3, vp = vplayout(1,4))
print(p4, vp = vplayout(2,1))
print(p5, vp = vplayout(2,2))
print(p6, vp = vplayout(2,3))
print(p7, vp = vplayout(2,4))

