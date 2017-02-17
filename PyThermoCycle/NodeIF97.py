
import seuif97 as if97

class Node(object):

    kwargs = {"t": 0.0,
              "p": 0.0,
              "x": None,
              "h": None,
              "s": None}
    status = 0
    msg = "Unknown variables"

    def __init__(self, **kwargs):
        self.p = None
        self.t = None
        self.h = None
        self.s = None
        self.x = None
        self.kwargs = Node.kwargs.copy()
        self.__call__(**kwargs)

    def __call__(self, **kwargs):
        self.kwargs.update(kwargs)
        if self.calculable:
            self.status = 1
            self.calculo()
            self.msg = "Solved"

    @property
    def calculable(self):
        """Check if class is calculable by its kwargs"""
        self._thermo = ""
        if self.kwargs["p"] and self.kwargs["t"]:
            self._thermo = "pt"
        elif self.kwargs["p"] and self.kwargs["h"] is not None:
            self._thermo = "ph"
        elif self.kwargs["p"] and self.kwargs["s"] is not None:
            self._thermo = "ps"
        elif self.kwargs["h"] is not None and self.kwargs["s"] is not None:
            self._thermo = "hs"
        elif self.kwargs["t"] and self.kwargs["x"] is not None:
            self._thermo = "tx"
        elif self.kwargs["p"] and self.kwargs["x"] is not None:
            self._thermo = "px"
        return self._thermo

    def calculo(self):
        args = (self.kwargs[self._thermo[0]], self.kwargs[self._thermo[1]])
        if self._thermo == "pt":
            self.p, self.t = args
            self.h = if97.pt2h(self.p, self.t)
            self.s = if97.pt2s(self.p, self.t)
            self.v = if97.pt2v(self.p, self.t)
            self.x = None
        elif self._thermo == "ph":
            self.p, self.h = args
            self.t = if97.ph2t(self.p, self.h)
            self.s = if97.ph2s(self.p, self.h)
            self.v = if97.ph2v(self.p, self.h)
            self.x = if97.ph2x(self.p, self.h)
        elif self._thermo == "ps":
            self.p, self.s = args
            self.t = if97.ps2t(self.p, self.s)
            self.h = if97.ps2h(self.p, self.s)
            self.v = if97.ps2v(self.p, self.s)
            self.x = if97.ps2x(self.p, self.s)
        elif self._thermo == "hs":
            self.h, self.s = args
            self.t = if97.hs2t(self.h, self.s)
            self.p = if97.hs2p(self.h, self.s)
            self.v = if97.hs2v(self.h, self.s)
            self.x = if97.hs2x(self.h, self.s)
        elif self._thermo == "px":
            self.p, self.x = args
            self.t = if97.px2t(self.p, self.x)
            self.h = if97.px2h(self.p, self.x)
            self.s = if97.px2s(self.p, self.x)
            self.v = if97.px2v(self.p, self.x)
        elif self._thermo == "tx":
            self.t, self.x = args
            self.p = if97.tx2p(self.t, self.x)
            self.h = if97.tx2h(self.t, self.x)
            self.s = if97.tx2s(self.t, self.x)
            self.v = if97.tx2v(self.tx, self.x)
