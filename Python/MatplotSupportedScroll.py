import matplotlib.pyplot

class Plot2D():
    def __init__(self, basescale = 1.25):
        self.basescale = basescale
        self.figure = matplotlib.pyplot.figure()
        self.ax = self.figure.add_subplot(111)
        self.ax.grid(linestyle='dashed')
        self.onZoom = self.ax.figure.canvas.mpl_connect('scroll_event', self.__zoom)

    def __zoom(self, event):
        if event.inaxes != self.ax.axes:
            return

        # calculate zoom size
        if event.button == 'up':
            self.scale = 1 / self.basescale
        elif event.button == 'down':
            self.scale = self.basescale
        else:
            self.scale = 1

        # get current x and y limits
        self.curXLim = self.ax.get_xlim()
        self.curYLim = self.ax.get_ylim()
        self.curXRange = (self.curXLim[1] - self.curXLim[0]) * self.scale
        self.curYRange = (self.curYLim[1] - self.curYLim[0]) * self.scale

        relX = (self.curXLim[1] - event.xdata) / (self.curXLim[1] - self.curXLim[0])
        relY = (self.curYLim[1] - event.ydata) / (self.curYLim[1] - self.curYLim[0])

        self.ax.set_xlim([event.xdata - self.curXRange * (1 - relX),
                          event.xdata + self.curXRange * relX])
        self.ax.set_ylim([event.ydata - self.curYRange * (1 - relY),
                          event.ydata + self.curYRange * relY])
        matplotlib.pyplot.draw()

if __name__ == "__main__":
    tmp = Plot2D()
    tmp.ax.plot(range(1, 20))
    tmp.ax.legend(["y=x"], loc="upper right")
    matplotlib.pyplot.show()