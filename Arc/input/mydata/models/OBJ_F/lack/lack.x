xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}


Frame Scene_Root {
 

 Frame cube {
  

  FrameTransformMatrix {
   1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.700000,0.000000,0.000000,0.039891,0.000000,1.000000;;
  }

  Mesh cube_obj {
   8;
   -0.500000;0.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   -0.500000;0.000000;0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;1.000000;0.500000;,
   0.500000;1.000000;0.500000;;
   12;
   3;0,2,3;,
   3;0,3,1;,
   3;0,1,5;,
   3;0,5,4;,
   3;0,4,6;,
   3;0,6,2;,
   3;1,3,7;,
   3;1,7,5;,
   3;2,6,7;,
   3;2,7,3;,
   3;4,5,7;,
   3;4,7,6;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cylinder {
  

  FrameTransformMatrix {
   0.020000,0.000000,0.000000,0.000000,0.000000,1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,-0.700000,0.000000,-0.300000,1.000000;;
  }

  Mesh cylinder_obj {
   18;
   0.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;1.000000;0.000000;,
   -0.707107;0.000000;0.707107;,
   -0.707107;1.000000;0.707107;,
   0.000000;0.000000;1.000000;,
   0.000000;1.000000;1.000000;,
   0.707107;0.000000;0.707107;,
   0.707107;1.000000;0.707107;,
   1.000000;0.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   0.707107;0.000000;-0.707107;,
   0.707107;1.000000;-0.707107;,
   0.000000;0.000000;-1.000000;,
   0.000000;1.000000;-1.000000;,
   -0.707107;0.000000;-0.707107;,
   -0.707107;1.000000;-0.707107;;
   32;
   3;4,2,0;,
   3;2,4,5;,
   3;2,5,3;,
   3;3,5,1;,
   3;6,4,0;,
   3;4,6,7;,
   3;4,7,5;,
   3;5,7,1;,
   3;8,6,0;,
   3;6,8,9;,
   3;6,9,7;,
   3;7,9,1;,
   3;10,8,0;,
   3;8,10,11;,
   3;8,11,9;,
   3;9,11,1;,
   3;12,10,0;,
   3;10,12,13;,
   3;10,13,11;,
   3;11,13,1;,
   3;14,12,0;,
   3;12,14,15;,
   3;12,15,13;,
   3;13,15,1;,
   3;16,14,0;,
   3;14,16,17;,
   3;14,17,15;,
   3;15,17,1;,
   3;2,16,0;,
   3;16,2,3;,
   3;16,3,17;,
   3;17,3,1;;

   MeshNormals {
    96;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    32;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;;
   }

   MeshMaterialList {
    1;
    32;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cylinder1 {
  

  FrameTransformMatrix {
   0.020000,0.000000,0.000000,0.000000,0.000000,1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,0.700000,0.000000,0.300000,1.000000;;
  }

  Mesh cylinder1_obj {
   18;
   0.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;1.000000;0.000000;,
   -0.707107;0.000000;0.707107;,
   -0.707107;1.000000;0.707107;,
   0.000000;0.000000;1.000000;,
   0.000000;1.000000;1.000000;,
   0.707107;0.000000;0.707107;,
   0.707107;1.000000;0.707107;,
   1.000000;0.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   0.707107;0.000000;-0.707107;,
   0.707107;1.000000;-0.707107;,
   0.000000;0.000000;-1.000000;,
   0.000000;1.000000;-1.000000;,
   -0.707107;0.000000;-0.707107;,
   -0.707107;1.000000;-0.707107;;
   32;
   3;4,2,0;,
   3;2,4,5;,
   3;2,5,3;,
   3;3,5,1;,
   3;6,4,0;,
   3;4,6,7;,
   3;4,7,5;,
   3;5,7,1;,
   3;8,6,0;,
   3;6,8,9;,
   3;6,9,7;,
   3;7,9,1;,
   3;10,8,0;,
   3;8,10,11;,
   3;8,11,9;,
   3;9,11,1;,
   3;12,10,0;,
   3;10,12,13;,
   3;10,13,11;,
   3;11,13,1;,
   3;14,12,0;,
   3;12,14,15;,
   3;12,15,13;,
   3;13,15,1;,
   3;16,14,0;,
   3;14,16,17;,
   3;14,17,15;,
   3;15,17,1;,
   3;2,16,0;,
   3;16,2,3;,
   3;16,3,17;,
   3;17,3,1;;

   MeshNormals {
    96;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    32;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;;
   }

   MeshMaterialList {
    1;
    32;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cylinder2 {
  

  FrameTransformMatrix {
   0.020000,0.000000,0.000000,0.000000,0.000000,1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,0.700000,0.000000,-0.300000,1.000000;;
  }

  Mesh cylinder2_obj {
   18;
   0.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;1.000000;0.000000;,
   -0.707107;0.000000;0.707107;,
   -0.707107;1.000000;0.707107;,
   0.000000;0.000000;1.000000;,
   0.000000;1.000000;1.000000;,
   0.707107;0.000000;0.707107;,
   0.707107;1.000000;0.707107;,
   1.000000;0.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   0.707107;0.000000;-0.707107;,
   0.707107;1.000000;-0.707107;,
   0.000000;0.000000;-1.000000;,
   0.000000;1.000000;-1.000000;,
   -0.707107;0.000000;-0.707107;,
   -0.707107;1.000000;-0.707107;;
   32;
   3;4,2,0;,
   3;2,4,5;,
   3;2,5,3;,
   3;3,5,1;,
   3;6,4,0;,
   3;4,6,7;,
   3;4,7,5;,
   3;5,7,1;,
   3;8,6,0;,
   3;6,8,9;,
   3;6,9,7;,
   3;7,9,1;,
   3;10,8,0;,
   3;8,10,11;,
   3;8,11,9;,
   3;9,11,1;,
   3;12,10,0;,
   3;10,12,13;,
   3;10,13,11;,
   3;11,13,1;,
   3;14,12,0;,
   3;12,14,15;,
   3;12,15,13;,
   3;13,15,1;,
   3;16,14,0;,
   3;14,16,17;,
   3;14,17,15;,
   3;15,17,1;,
   3;2,16,0;,
   3;16,2,3;,
   3;16,3,17;,
   3;17,3,1;;

   MeshNormals {
    96;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    32;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;;
   }

   MeshMaterialList {
    1;
    32;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cylinder3 {
  

  FrameTransformMatrix {
   0.020000,0.000000,0.000000,0.000000,0.000000,1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,-0.700000,0.000000,0.300000,1.000000;;
  }

  Mesh cylinder3_obj {
   18;
   0.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   -1.000000;1.000000;0.000000;,
   -0.707107;0.000000;0.707107;,
   -0.707107;1.000000;0.707107;,
   0.000000;0.000000;1.000000;,
   0.000000;1.000000;1.000000;,
   0.707107;0.000000;0.707107;,
   0.707107;1.000000;0.707107;,
   1.000000;0.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   0.707107;0.000000;-0.707107;,
   0.707107;1.000000;-0.707107;,
   0.000000;0.000000;-1.000000;,
   0.000000;1.000000;-1.000000;,
   -0.707107;0.000000;-0.707107;,
   -0.707107;1.000000;-0.707107;;
   32;
   3;4,2,0;,
   3;2,4,5;,
   3;2,5,3;,
   3;3,5,1;,
   3;6,4,0;,
   3;4,6,7;,
   3;4,7,5;,
   3;5,7,1;,
   3;8,6,0;,
   3;6,8,9;,
   3;6,9,7;,
   3;7,9,1;,
   3;10,8,0;,
   3;8,10,11;,
   3;8,11,9;,
   3;9,11,1;,
   3;12,10,0;,
   3;10,12,13;,
   3;10,13,11;,
   3;11,13,1;,
   3;14,12,0;,
   3;12,14,15;,
   3;12,15,13;,
   3;13,15,1;,
   3;16,14,0;,
   3;14,16,17;,
   3;14,17,15;,
   3;15,17,1;,
   3;2,16,0;,
   3;16,2,3;,
   3;16,3,17;,
   3;17,3,1;;

   MeshNormals {
    96;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    32;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;;
   }

   MeshMaterialList {
    1;
    32;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cube1 {
  

  FrameTransformMatrix {
   1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.700000,0.000000,0.000000,1.487462,0.000000,1.000000;;
  }

  Mesh cube1_obj {
   8;
   -0.500000;0.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   -0.500000;0.000000;0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;1.000000;0.500000;,
   0.500000;1.000000;0.500000;;
   12;
   3;0,2,3;,
   3;0,3,1;,
   3;0,1,5;,
   3;0,5,4;,
   3;0,4,6;,
   3;0,6,2;,
   3;1,3,7;,
   3;1,7,5;,
   3;2,6,7;,
   3;2,7,3;,
   3;4,5,7;,
   3;4,7,6;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cube2 {
  

  FrameTransformMatrix {
   1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.700000,0.000000,0.000000,0.504817,0.000000,1.000000;;
  }

  Mesh cube2_obj {
   8;
   -0.500000;0.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   -0.500000;0.000000;0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;1.000000;0.500000;,
   0.500000;1.000000;0.500000;;
   12;
   3;0,2,3;,
   3;0,3,1;,
   3;0,1,5;,
   3;0,5,4;,
   3;0,4,6;,
   3;0,6,2;,
   3;1,3,7;,
   3;1,7,5;,
   3;2,6,7;,
   3;2,7,3;,
   3;4,5,7;,
   3;4,7,6;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }

 Frame cube3 {
  

  FrameTransformMatrix {
   1.500000,0.000000,0.000000,0.000000,0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.700000,0.000000,0.000000,1.047641,0.000000,1.000000;;
  }

  Mesh cube3_obj {
   8;
   -0.500000;0.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   -0.500000;0.000000;0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;1.000000;0.500000;,
   0.500000;1.000000;0.500000;;
   12;
   3;0,2,3;,
   3;0,3,1;,
   3;0,1,5;,
   3;0,5,4;,
   3;0,4,6;,
   3;0,6,2;,
   3;1,3,7;,
   3;1,7,5;,
   3;2,6,7;,
   3;2,7,3;,
   3;4,5,7;,
   3;4,7,6;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Scene_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;
    }
   }
  }
 }
}