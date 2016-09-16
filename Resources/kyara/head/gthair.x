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

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
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

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Frame Scene_Root {
 

 Frame hiar1 {
  

  FrameTransformMatrix {
   -0.001257,-0.049901,-0.189326,0.000000,0.081388,-1.504663,0.396050,0.000000,-1.159619,-0.056760,0.022661,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh hiar1_obj {
   12;
   0.669467;-0.133616;0.447046;,
   0.669467;-0.133616;-0.418979;,
   0.000000;0.666667;0.000000;,
   -0.251373;-0.126556;0.014534;,
   0.669467;-0.133616;0.447046;,
   0.000000;0.666667;0.000000;,
   0.669467;-0.133616;-0.418979;,
   -0.251373;-0.126556;0.014534;,
   0.000000;0.666667;0.000000;,
   -0.251373;-0.126556;0.014534;,
   0.669467;-0.133616;-0.418979;,
   0.669467;-0.133616;0.447046;;
   4;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;;

   MeshNormals {
    12;
    0.767011;0.641634;0.000000;,
    0.767011;0.641634;0.000000;,
    0.767011;0.641634;0.000000;,
    -0.419429;0.149324;0.895422;,
    -0.419429;0.149324;0.895422;,
    -0.419429;0.149324;0.895422;,
    -0.422260;0.117345;-0.898847;,
    -0.422260;0.117345;-0.898847;,
    -0.422260;0.117345;-0.898847;,
    -0.007667;-0.999971;0.000000;,
    -0.007667;-0.999971;0.000000;,
    -0.007667;-0.999971;0.000000;;
    4;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;;
   }

   MeshTextureCoords {
    12;
    -0.677754;-0.194187;,
    -0.766595;-0.220266;,
    -0.704691;-0.269611;,
    -0.677754;-0.194187;,
    -0.766595;-0.220266;,
    -0.704691;-0.269611;,
    -0.677754;-0.194187;,
    -0.766595;-0.220266;,
    -0.704691;-0.269611;,
    -0.491585;0.746792;,
    -1.291186;0.640896;,
    -0.916820;0.640896;;
   }

   MeshMaterialList {
    1;
    4;
    0,
    0,
    0,
    0;

    Material DefaultLib_Material9 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "hair.bmp";
     }
    }
   }
  }
 }
}