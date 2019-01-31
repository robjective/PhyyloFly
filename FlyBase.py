import bpy
import math
import mathutils
from mathutils import Euler
# make sure 3d cursor is at the center of the scene

n = 18 # number of points
c = 0.7 # scale factor

for i in range(10, n):
    theta = i * math.radians(137.5)
    r = c * math.sqrt(i)
    # add cone, modify the mesh,
    bpy.ops.mesh.primitive_cone_add(vertices=12, radius1=0.5, depth=5)
    obj = bpy.context.active_object
    obj.location = (math.cos(theta) * r, math.sin(theta) * r, i*c*.05)
    #bj.rotation_mode = 'XYZ'
    #obj.rotation_euler = (rx, ry, rz)
    #define direction
    #Vector=(math.cos(theta) * 5,math.sin(theta) * 5 ,10)
    Vector=(math.cos(theta) * 10,math.sin(theta) * 10 ,10)
    DirectionVector = mathutils.Vector(Vector) 
    #apply rotation
    obj.rotation_mode = 'QUATERNION'
    obj.rotation_quaternion = DirectionVector.to_track_quat('Z','Y')
   
