
import NodeIF97

tNode = NodeIF97.Node(p=16.2,t=535)
print(tNode.h)

tNode = NodeIF97.Node(p=16.2,h=tNode.h)
print(tNode.t)

tNode = NodeIF97.Node(i=16.2,t=535)
print(tNode.h)


