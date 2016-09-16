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
 

 Frame door {
  

  FrameTransformMatrix {
   0.117939,0.000000,0.000000,0.000000,0.000000,0.205703,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,-0.000035,0.000000,0.000000,1.000000;;
  }

  Mesh door_obj {
   36;
   0.000035;0.000000;-4.000000;,
   0.000035;8.000000;-4.000000;,
   8.000035;8.000000;-4.000000;,
   0.000035;0.000000;-4.000000;,
   8.000035;8.000000;-4.000000;,
   8.000035;0.000000;-4.000000;,
   0.000035;0.000000;-4.000000;,
   8.000035;0.000000;-4.000000;,
   8.000035;0.000000;4.000000;,
   0.000035;0.000000;-4.000000;,
   8.000035;0.000000;4.000000;,
   0.000035;0.000000;4.000000;,
   0.000035;0.000000;-4.000000;,
   0.000035;0.000000;4.000000;,
   0.000035;8.000000;4.000000;,
   0.000035;0.000000;-4.000000;,
   0.000035;8.000000;4.000000;,
   0.000035;8.000000;-4.000000;,
   8.000035;0.000000;-4.000000;,
   8.000035;8.000000;-4.000000;,
   8.000035;8.000000;4.000000;,
   8.000035;0.000000;-4.000000;,
   8.000035;8.000000;4.000000;,
   8.000035;0.000000;4.000000;,
   0.000035;8.000000;-4.000000;,
   0.000035;8.000000;4.000000;,
   8.000035;8.000000;4.000000;,
   0.000035;8.000000;-4.000000;,
   8.000035;8.000000;4.000000;,
   8.000035;8.000000;-4.000000;,
   0.000035;0.000000;4.000000;,
   8.000035;0.000000;4.000000;,
   8.000035;8.000000;4.000000;,
   0.000035;0.000000;4.000000;,
   8.000035;8.000000;4.000000;,
   0.000035;8.000000;4.000000;;
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

   MeshTextureCoords {
    36;
    -1.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;-1.000000;,
    -1.000000;0.000000;,
    0.000000;-1.000000;,
    0.000000;0.000000;,
    0.000000;0.000000;,
    -1.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;-1.000000;,
    0.000000;0.000000;,
    -1.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;-1.000000;,
    -1.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;-1.000000;,
    -1.000000;0.000000;,
    0.000000;-1.000000;,
    0.000000;0.000000;,
    0.000000;-1.000000;,
    0.000000;0.000000;,
    -1.000000;0.000000;,
    0.000000;-1.000000;,
    -1.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;0.000000;,
    -1.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;0.000000;,
    -1.000000;-1.000000;,
    0.000000;-1.000000;;
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

    Material DefaultLib_Material24 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "ki.bmp";
     }
    }
   }
  }
 }

 Frame nobu_cube {
  

  FrameTransformMatrix {
   0.714378,0.000000,0.000000,0.000000,0.000000,1.570625,0.000000,0.000000,0.000000,0.000000,1.057028,0.000000,0.824394,0.753953,-0.000569,1.000000;;
  }

  Mesh nobu_cube_obj {
   36;
   -0.050000;-0.050000;-0.050000;,
   -0.050000;0.050000;-0.050000;,
   0.050000;0.050000;-0.050000;,
   -0.050000;-0.050000;-0.050000;,
   0.050000;0.050000;-0.050000;,
   0.050000;-0.050000;-0.050000;,
   -0.050000;-0.050000;-0.050000;,
   0.050000;-0.050000;-0.050000;,
   0.050000;-0.050000;0.050000;,
   -0.050000;-0.050000;-0.050000;,
   0.050000;-0.050000;0.050000;,
   -0.050000;-0.050000;0.050000;,
   -0.050000;-0.050000;-0.050000;,
   -0.050000;-0.050000;0.050000;,
   -0.050000;0.050000;0.050000;,
   -0.050000;-0.050000;-0.050000;,
   -0.050000;0.050000;0.050000;,
   -0.050000;0.050000;-0.050000;,
   0.050000;-0.050000;-0.050000;,
   0.050000;0.050000;-0.050000;,
   0.050000;0.050000;0.050000;,
   0.050000;-0.050000;-0.050000;,
   0.050000;0.050000;0.050000;,
   0.050000;-0.050000;0.050000;,
   -0.050000;0.050000;-0.050000;,
   -0.050000;0.050000;0.050000;,
   0.050000;0.050000;0.050000;,
   -0.050000;0.050000;-0.050000;,
   0.050000;0.050000;0.050000;,
   0.050000;0.050000;-0.050000;,
   0.050000;0.050000;0.050000;,
   -0.050000;0.050000;0.050000;,
   -0.050000;-0.050000;0.050000;,
   0.050000;0.050000;0.050000;,
   -0.050000;-0.050000;0.050000;,
   0.050000;-0.050000;0.050000;;
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

   MeshTextureCoords {
    36;
    -0.516156;-0.960656;,
    -0.516156;-0.991214;,
    -0.485598;-0.991214;,
    -0.516156;-0.960656;,
    -0.485598;-0.991214;,
    -0.485598;-0.960656;,
    -0.485598;-0.960656;,
    -0.516156;-0.960656;,
    -0.516156;-0.991214;,
    -0.485598;-0.960656;,
    -0.516156;-0.991214;,
    -0.485598;-0.991214;,
    -0.485598;-0.960656;,
    -0.516156;-0.960656;,
    -0.516156;-0.991214;,
    -0.485598;-0.960656;,
    -0.516156;-0.991214;,
    -0.485598;-0.991214;,
    -0.516156;-0.960656;,
    -0.516156;-0.991214;,
    -0.485598;-0.991214;,
    -0.516156;-0.960656;,
    -0.485598;-0.991214;,
    -0.485598;-0.960656;,
    -0.485598;-0.991214;,
    -0.485598;-0.960656;,
    -0.516156;-0.960656;,
    -0.485598;-0.991214;,
    -0.516156;-0.960656;,
    -0.516156;-0.991214;,
    -0.516156;-0.960656;,
    -0.485598;-0.960656;,
    -0.516156;-0.960656;,
    -0.516156;-0.960656;,
    -0.516156;-0.960656;,
    -0.516156;-0.991214;;
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

    Material DefaultLib_Material25 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "ki1.bmp";
     }
    }
   }
  }
 }
}