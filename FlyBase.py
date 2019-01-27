import bpy
import math
import mathutils
from mathutils import Euler
# make sure 3d cursor is at the center of the scene

n = 15 # number of points
c = 0.5 # scale factor

for i in range(0, n):
    theta = i * math.radians(137.5)
    r = c * math.sqrt(i)
    # add cone, modify the mesh,
    bpy.ops.mesh.primitive_cone_add(vertices=12, radius1=0.5, depth=1)
    obj = bpy.context.active_object
    obj.location = (math.cos(theta) * r, math.sin(theta) * r, 0)
    obj.rotation_mode = 'XYZ'
    # obj.rotation_euler = (rx, ry, rz)


