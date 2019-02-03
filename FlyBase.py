import bpy
import math
import mathutils
from mathutils import Euler
# make sure 3d cursor is at the center of the scene

n = 38 # number of points
c = 1.1 # scale factor

for i in range(10, n):
    theta = i * math.radians(137.5)
    r = c * math.sqrt(i)
    Vector=(math.cos(theta) * 10,math.sin(theta) * 10 ,10)
    DirectionVector = mathutils.Vector(Vector) 
    # add cone, modify the mesh,

    bpy.ops.mesh.primitive_cone_add(vertices=12, radius1=1, depth=10)
    obj1 = bpy.context.active_object
    obj1.location = (math.cos(theta) * r, math.sin(theta) * r, 0)
   
    #apply rotation
    obj1.rotation_mode = 'QUATERNION'
    obj1.rotation_quaternion = DirectionVector.to_track_quat('Z','Y')
    
    # Add Cylinder
    bpy.ops.mesh.primitive_cylinder_add(radius=.08, depth=12, view_align=False )
    obj2 = bpy.context.active_object
    obj2.location = (math.cos(theta) * r, math.sin(theta) * r, 0)
    obj2.rotation_mode = 'QUATERNION'
    obj2.rotation_quaternion = DirectionVector.to_track_quat('Z','Y')
  
   # bpy.context.space_data.context = 'MODIFIER'
    obj1.modifiers.new("booh",'BOOLEAN')
    obj1.modifiers["booh"].operation = 'DIFFERENCE'
    obj1.modifiers["booh"].object = obj2
    bpy.context.scene.objects.active = obj1 #sets the obj accessible to bpy.ops
    bpy.ops.object.modifier_apply(apply_as='DATA', modifier="booh")

    # Remove the cyliners
scene = bpy.context.scene

for ob in scene.objects:
    if ob.type == 'MESH' and ob.name.startswith("Cylinder"):
        ob.select = True
    else: 
        ob.select = False

bpy.ops.object.delete()    
bpy.ops.mesh.primitive_cylinder_add(radius=1, depth=12, view_align=False )
obj2 = bpy.context.active_object
obj2.location = (0,0, 0)
    # obj1.modifier_apply(apply_as='DATA', modifier="booh")

# Join the cones together
active=object = bpy.data.objects['Cone']
for ob in scene.objects:
    if ob.type == 'MESH' and ob.name.startswith("Cone") and ob.name!="Cone":
        ob.select = True
    else: 
        ob.select = False

print('active:', active.name)
print('selected (not active):', [o.name for o in bpy.context.selected_objects])

for idx, joiner in enumerate(bpy.context.selected_objects):
    bool_mod = active.modifiers.new('joiner_' + str(idx), 'BOOLEAN')
    bool_mod.operation = 'UNION'
    bool_mod.object = joiner
    joiner.hide = True
