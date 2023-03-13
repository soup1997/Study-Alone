'''
generate_opendrive_world(self, opendrive, parameters=(2.0, 50.0, 1.0, 0.6, true, true), reset_settings=True)

Loads a new world with a basic 3D topology generated from the content of an OpenDRIVE file. This content is passed as a string parameter. 
It is similar to client.load_world(map_name) but allows for custom OpenDRIVE maps in server side. 
Cars can drive around the map, but there are no graphics besides the road and sidewalks.

Parameters:
    opendrive (str) - Content of an OpenDRIVE file as string, not the path to the .xodr.
    parameters:
        vertex_distance (float) - Distance between vertices of the mesh generated. Default is 2.0.
        
        max_road_length (float) - Max road length for a single mesh portion. The mesh of the map is divided into portions, in order to avoid propagating issues. Default is 50.0.
        
        wall_height (float) - Height of walls created on the boundaries of the road. These prevent vehicles from falling off the road. Default is 1.0.
        
        additional_width (float) - Additional with applied junction lanes. Complex situations tend to occur at junctions, and a little increase can prevent vehicles from falling off the road. Default is 0.6.
        
        smooth_junctions (bool) - If True, the mesh at junctions will be smoothed to prevent issues where roads blocked other roads. Default is True.
        
        enable_mesh_visibility (bool) - If True, the road mesh will be rendered. Setting this to False should reduce the rendering overhead. Default is True.
        
        enable_pedestrian_navigation (bool) - If True, Pedestrian navigation will be enabled using Recast tool. For very large maps it is recomended to disable this option. Default is True.
    reset_settings (bool) - Option to reset the episode setting to default values, set to false to keep the current settings. This is useful to keep sync mode when changing map and to keep deterministic scenarios.
    
    
'''

vertex_distance = 2.0
max_road_length = 50.0
wall_height = 1.0      
extra_width = 0.6
additonal_width = 0.6

smooth_junctions = True
enable_mesh_visibility = True
enable_pedestrian_navigation = False