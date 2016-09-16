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
 

 Frame cube1 {
  

  FrameTransformMatrix {
   0.545865,0.000000,0.000000,0.000000,0.000000,0.900000,0.000000,0.000000,0.000000,0.000000,0.027820,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh cube1_obj {
   36;
   0.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   1.000000;0.000000;1.000000;,
   0.000000;0.000000;0.000000;,
   1.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;1.000000;1.000000;,
   0.000000;0.000000;0.000000;,
   0.000000;1.000000;1.000000;,
   0.000000;1.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   1.000000;1.000000;0.000000;,
   1.000000;1.000000;1.000000;,
   1.000000;0.000000;0.000000;,
   1.000000;1.000000;1.000000;,
   1.000000;0.000000;1.000000;,
   0.000000;1.000000;0.000000;,
   0.000000;1.000000;1.000000;,
   1.000000;1.000000;1.000000;,
   0.000000;1.000000;0.000000;,
   1.000000;1.000000;1.000000;,
   1.000000;1.000000;0.000000;,
   0.000000;0.000000;1.000000;,
   1.000000;0.000000;1.000000;,
   1.000000;1.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   1.000000;1.000000;1.000000;,
   0.000000;1.000000;1.000000;;
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
    -1.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.730000;,
    -1.000000;-0.010000;,
    0.000000;-0.730000;,
    0.000000;-0.010000;,
    0.000000;-0.010000;,
    -1.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.730000;,
    0.000000;-0.010000;,
    -1.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.730000;,
    -1.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.730000;,
    -1.000000;-0.010000;,
    0.000000;-0.730000;,
    0.000000;-0.010000;,
    0.000000;-0.730000;,
    0.000000;-0.010000;,
    -1.000000;-0.010000;,
    0.000000;-0.730000;,
    -1.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.010000;,
    -1.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.010000;,
    -1.000000;-0.730000;,
    0.000000;-0.730000;;
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

    Material DefaultLib_Material9 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "reizouko.bmp";
     }
    }
   }
  }
 }

 Frame cylinder {
  

  FrameTransformMatrix {
   0.592824,0.000000,0.000000,0.000000,0.000000,0.054153,0.042578,0.000000,0.000000,-0.162237,0.206341,0.000000,0.482807,0.491985,0.018789,1.000000;;
  }

  Mesh cylinder_obj {
   192;
   -0.021213;0.000000;0.021213;,
   -0.030000;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   -0.030000;0.000000;0.000000;,
   -0.021213;0.000000;0.021213;,
   -0.021213;1.000000;0.021213;,
   -0.030000;0.000000;0.000000;,
   -0.021213;1.000000;0.021213;,
   -0.030000;1.000000;0.000000;,
   -0.030000;2.489736;-0.545121;,
   -0.021213;2.570553;-0.545121;,
   0.000000;2.489736;-0.545121;,
   0.000000;0.000000;0.030000;,
   -0.021213;0.000000;0.021213;,
   0.000000;0.000000;0.000000;,
   -0.021213;0.000000;0.021213;,
   0.000000;0.000000;0.030000;,
   0.000000;1.000000;0.030000;,
   -0.021213;0.000000;0.021213;,
   0.000000;1.000000;0.030000;,
   -0.021213;1.000000;0.021213;,
   -0.021213;2.570553;-0.545121;,
   0.000000;2.604028;-0.545121;,
   0.000000;2.489736;-0.545121;,
   0.021213;0.000000;0.021213;,
   0.000000;0.000000;0.030000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.000000;0.030000;,
   0.021213;0.000000;0.021213;,
   0.021213;1.000000;0.021213;,
   0.000000;0.000000;0.030000;,
   0.021213;1.000000;0.021213;,
   0.000000;1.000000;0.030000;,
   0.000000;2.604028;-0.545121;,
   0.021213;2.570553;-0.545121;,
   0.000000;2.489736;-0.545121;,
   0.030000;0.000000;0.000000;,
   0.021213;0.000000;0.021213;,
   0.000000;0.000000;0.000000;,
   0.021213;0.000000;0.021213;,
   0.030000;0.000000;0.000000;,
   0.030000;1.000000;0.000000;,
   0.021213;0.000000;0.021213;,
   0.030000;1.000000;0.000000;,
   0.021213;1.000000;0.021213;,
   0.021213;2.570553;-0.545121;,
   0.030000;2.489736;-0.545121;,
   0.000000;2.489736;-0.545121;,
   0.021213;0.000000;-0.021213;,
   0.030000;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   0.030000;0.000000;0.000000;,
   0.021213;0.000000;-0.021213;,
   0.021213;1.000000;-0.021213;,
   0.030000;0.000000;0.000000;,
   0.021213;1.000000;-0.021213;,
   0.030000;1.000000;0.000000;,
   0.030000;2.489736;-0.545121;,
   0.021213;2.408919;-0.545121;,
   0.000000;2.489736;-0.545121;,
   0.000000;0.000000;-0.030000;,
   0.021213;0.000000;-0.021213;,
   0.000000;0.000000;0.000000;,
   0.021213;0.000000;-0.021213;,
   0.000000;0.000000;-0.030000;,
   0.000000;1.000000;-0.030000;,
   0.021213;0.000000;-0.021213;,
   0.000000;1.000000;-0.030000;,
   0.021213;1.000000;-0.021213;,
   0.021213;2.408919;-0.545121;,
   0.000000;2.375444;-0.545121;,
   0.000000;2.489736;-0.545121;,
   -0.021213;0.000000;-0.021213;,
   0.000000;0.000000;-0.030000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.000000;-0.030000;,
   -0.021213;0.000000;-0.021213;,
   -0.021213;1.000000;-0.021213;,
   0.000000;0.000000;-0.030000;,
   -0.021213;1.000000;-0.021213;,
   0.000000;1.000000;-0.030000;,
   0.000000;2.375444;-0.545121;,
   -0.021213;2.408919;-0.545121;,
   0.000000;2.489736;-0.545121;,
   -0.030000;0.000000;0.000000;,
   -0.021213;0.000000;-0.021213;,
   0.000000;0.000000;0.000000;,
   -0.021213;0.000000;-0.021213;,
   -0.030000;0.000000;0.000000;,
   -0.030000;1.000000;0.000000;,
   -0.021213;0.000000;-0.021213;,
   -0.030000;1.000000;0.000000;,
   -0.021213;1.000000;-0.021213;,
   -0.021213;2.408919;-0.545121;,
   -0.030000;2.489736;-0.545121;,
   0.000000;2.489736;-0.545121;,
   -0.030000;1.000000;0.000000;,
   -0.021213;1.000000;0.021213;,
   -0.021213;2.467592;-0.274370;,
   -0.030000;1.000000;0.000000;,
   -0.021213;2.467592;-0.274370;,
   -0.030000;2.386776;-0.274370;,
   -0.021213;1.000000;0.021213;,
   0.000000;1.000000;0.030000;,
   0.000000;2.501068;-0.274370;,
   -0.021213;1.000000;0.021213;,
   0.000000;2.501068;-0.274370;,
   -0.021213;2.467592;-0.274370;,
   0.000000;1.000000;0.030000;,
   0.021213;1.000000;0.021213;,
   0.021213;2.467592;-0.274370;,
   0.000000;1.000000;0.030000;,
   0.021213;2.467592;-0.274370;,
   0.000000;2.501068;-0.274370;,
   0.021213;1.000000;0.021213;,
   0.030000;1.000000;0.000000;,
   0.030000;2.386776;-0.274370;,
   0.021213;1.000000;0.021213;,
   0.030000;2.386776;-0.274370;,
   0.021213;2.467592;-0.274370;,
   0.030000;1.000000;0.000000;,
   0.021213;1.000000;-0.021213;,
   0.021213;2.305959;-0.274370;,
   0.030000;1.000000;0.000000;,
   0.021213;2.305959;-0.274370;,
   0.030000;2.386776;-0.274370;,
   0.021213;1.000000;-0.021213;,
   0.000000;1.000000;-0.030000;,
   0.000000;2.272484;-0.274370;,
   0.021213;1.000000;-0.021213;,
   0.000000;2.272484;-0.274370;,
   0.021213;2.305959;-0.274370;,
   0.000000;1.000000;-0.030000;,
   -0.021213;1.000000;-0.021213;,
   -0.021213;2.305959;-0.274370;,
   0.000000;1.000000;-0.030000;,
   -0.021213;2.305959;-0.274370;,
   0.000000;2.272484;-0.274370;,
   -0.021213;1.000000;-0.021213;,
   -0.030000;1.000000;0.000000;,
   -0.030000;2.386776;-0.274370;,
   -0.021213;1.000000;-0.021213;,
   -0.030000;2.386776;-0.274370;,
   -0.021213;2.305959;-0.274370;,
   -0.030000;2.386776;-0.274370;,
   -0.021213;2.467592;-0.274370;,
   -0.021213;2.570553;-0.545121;,
   -0.030000;2.386776;-0.274370;,
   -0.021213;2.570553;-0.545121;,
   -0.030000;2.489736;-0.545121;,
   -0.021213;2.467592;-0.274370;,
   0.000000;2.501068;-0.274370;,
   0.000000;2.604028;-0.545121;,
   -0.021213;2.467592;-0.274370;,
   0.000000;2.604028;-0.545121;,
   -0.021213;2.570553;-0.545121;,
   0.000000;2.501068;-0.274370;,
   0.021213;2.467592;-0.274370;,
   0.021213;2.570553;-0.545121;,
   0.000000;2.501068;-0.274370;,
   0.021213;2.570553;-0.545121;,
   0.000000;2.604028;-0.545121;,
   0.021213;2.467592;-0.274370;,
   0.030000;2.386776;-0.274370;,
   0.030000;2.489736;-0.545121;,
   0.021213;2.467592;-0.274370;,
   0.030000;2.489736;-0.545121;,
   0.021213;2.570553;-0.545121;,
   0.030000;2.386776;-0.274370;,
   0.021213;2.305959;-0.274370;,
   0.021213;2.408919;-0.545121;,
   0.030000;2.386776;-0.274370;,
   0.021213;2.408919;-0.545121;,
   0.030000;2.489736;-0.545121;,
   0.021213;2.305959;-0.274370;,
   0.000000;2.272484;-0.274370;,
   0.000000;2.375444;-0.545121;,
   0.021213;2.305959;-0.274370;,
   0.000000;2.375444;-0.545121;,
   0.021213;2.408919;-0.545121;,
   0.000000;2.272484;-0.274370;,
   -0.021213;2.305959;-0.274370;,
   -0.021213;2.408919;-0.545121;,
   0.000000;2.272484;-0.274370;,
   -0.021213;2.408919;-0.545121;,
   0.000000;2.375444;-0.545121;,
   -0.021213;2.305959;-0.274370;,
   -0.030000;2.386776;-0.274370;,
   -0.030000;2.489736;-0.545121;,
   -0.021213;2.305959;-0.274370;,
   -0.030000;2.489736;-0.545121;,
   -0.021213;2.408919;-0.545121;;
   64;
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
   3;93,94,95;,
   3;96,97,98;,
   3;99,100,101;,
   3;102,103,104;,
   3;105,106,107;,
   3;108,109,110;,
   3;111,112,113;,
   3;114,115,116;,
   3;117,118,119;,
   3;120,121,122;,
   3;123,124,125;,
   3;126,127,128;,
   3;129,130,131;,
   3;132,133,134;,
   3;135,136,137;,
   3;138,139,140;,
   3;141,142,143;,
   3;144,145,146;,
   3;147,148,149;,
   3;150,151,152;,
   3;153,154,155;,
   3;156,157,158;,
   3;159,160,161;,
   3;162,163,164;,
   3;165,166,167;,
   3;168,169,170;,
   3;171,172,173;,
   3;174,175,176;,
   3;177,178,179;,
   3;180,181,182;,
   3;183,184,185;,
   3;186,187,188;,
   3;189,190,191;;

   MeshNormals {
    192;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -0.690545;0.073529;0.719542;,
    -1.000000;0.000000;0.000000;,
    -0.690545;0.073529;0.719542;,
    -1.000000;0.000283;-0.000791;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;0.100459;0.994941;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.100459;0.994941;,
    -0.690545;0.073529;0.719542;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.690545;0.073529;0.719542;,
    0.000000;0.000000;1.000000;,
    0.690545;0.073529;0.719542;,
    0.000000;0.100459;0.994941;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000283;-0.000791;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000283;-0.000791;,
    0.690545;0.073529;0.719542;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.688857;-0.071157;-0.721396;,
    1.000000;0.000000;0.000000;,
    0.688857;-0.071157;-0.721396;,
    1.000000;0.000283;-0.000791;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;-0.096138;-0.995368;,
    0.707107;0.000000;-0.707107;,
    0.000000;-0.096138;-0.995368;,
    0.688857;-0.071157;-0.721396;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    -0.688857;-0.071157;-0.721396;,
    0.000000;0.000000;-1.000000;,
    -0.688857;-0.071157;-0.721396;,
    0.000000;-0.096138;-0.995368;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000283;-0.000791;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000283;-0.000791;,
    -0.688857;-0.071157;-0.721396;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    -1.000000;0.000283;-0.000791;,
    -0.690545;0.073529;0.719542;,
    -0.858735;0.253529;0.445306;,
    -1.000000;0.000283;-0.000791;,
    -0.858735;0.253529;0.445306;,
    -1.000000;0.000273;-0.000762;,
    -0.690545;0.073529;0.719542;,
    0.000000;0.100459;0.994941;,
    0.000000;0.535265;0.844684;,
    -0.690545;0.073529;0.719542;,
    0.000000;0.535265;0.844684;,
    -0.858735;0.253529;0.445306;,
    0.000000;0.100459;0.994941;,
    0.690545;0.073529;0.719542;,
    0.858735;0.253529;0.445306;,
    0.000000;0.100459;0.994941;,
    0.858735;0.253529;0.445306;,
    0.000000;0.535265;0.844684;,
    0.690545;0.073529;0.719542;,
    1.000000;0.000283;-0.000791;,
    1.000000;0.000273;-0.000762;,
    0.690545;0.073529;0.719542;,
    1.000000;0.000273;-0.000762;,
    0.858735;0.253529;0.445306;,
    1.000000;0.000283;-0.000791;,
    0.688857;-0.071157;-0.721396;,
    0.858091;-0.251422;-0.447736;,
    1.000000;0.000283;-0.000791;,
    0.858091;-0.251422;-0.447736;,
    1.000000;0.000273;-0.000762;,
    0.688857;-0.071157;-0.721396;,
    0.000000;-0.096138;-0.995368;,
    0.000000;-0.529894;-0.848064;,
    0.688857;-0.071157;-0.721396;,
    0.000000;-0.529894;-0.848064;,
    0.858091;-0.251422;-0.447736;,
    0.000000;-0.096138;-0.995368;,
    -0.688857;-0.071157;-0.721396;,
    -0.858091;-0.251422;-0.447736;,
    0.000000;-0.096138;-0.995368;,
    -0.858091;-0.251422;-0.447736;,
    0.000000;-0.529894;-0.848064;,
    -0.688857;-0.071157;-0.721396;,
    -1.000000;0.000283;-0.000791;,
    -1.000000;0.000273;-0.000762;,
    -0.688857;-0.071157;-0.721396;,
    -1.000000;0.000273;-0.000762;,
    -0.858091;-0.251422;-0.447736;,
    -1.000000;0.000273;-0.000762;,
    -0.858735;0.253529;0.445306;,
    -0.937370;0.325587;0.123813;,
    -1.000000;0.000273;-0.000762;,
    -0.937370;0.325587;0.123813;,
    -1.000000;0.000000;0.000000;,
    -0.858735;0.253529;0.445306;,
    0.000000;0.535265;0.844684;,
    -0.827707;0.524515;0.199460;,
    -0.858735;0.253529;0.445306;,
    -0.827707;0.524515;0.199460;,
    -0.937370;0.325587;0.123813;,
    0.000000;0.535265;0.844684;,
    0.858735;0.253529;0.445306;,
    0.937370;0.325587;0.123813;,
    0.000000;0.535265;0.844684;,
    0.937370;0.325587;0.123813;,
    0.827707;0.524515;0.199460;,
    0.858735;0.253529;0.445306;,
    1.000000;0.000273;-0.000762;,
    1.000000;0.000000;0.000000;,
    0.858735;0.253529;0.445306;,
    1.000000;0.000000;0.000000;,
    0.937370;0.325587;0.123813;,
    1.000000;0.000273;-0.000762;,
    0.858091;-0.251422;-0.447736;,
    0.937370;-0.325587;-0.123813;,
    1.000000;0.000273;-0.000762;,
    0.937370;-0.325587;-0.123813;,
    1.000000;0.000000;0.000000;,
    0.858091;-0.251422;-0.447736;,
    0.000000;-0.529894;-0.848064;,
    0.827707;-0.524515;-0.199460;,
    0.858091;-0.251422;-0.447736;,
    0.827707;-0.524515;-0.199460;,
    0.937370;-0.325587;-0.123813;,
    0.000000;-0.529894;-0.848064;,
    -0.858091;-0.251422;-0.447736;,
    -0.937370;-0.325587;-0.123813;,
    0.000000;-0.529894;-0.848064;,
    -0.937370;-0.325587;-0.123813;,
    -0.827707;-0.524515;-0.199460;,
    -0.858091;-0.251422;-0.447736;,
    -1.000000;0.000273;-0.000762;,
    -1.000000;0.000000;0.000000;,
    -0.858091;-0.251422;-0.447736;,
    -1.000000;0.000000;0.000000;,
    -0.937370;-0.325587;-0.123813;;
    64;
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
    3;93,94,95;,
    3;96,97,98;,
    3;99,100,101;,
    3;102,103,104;,
    3;105,106,107;,
    3;108,109,110;,
    3;111,112,113;,
    3;114,115,116;,
    3;117,118,119;,
    3;120,121,122;,
    3;123,124,125;,
    3;126,127,128;,
    3;129,130,131;,
    3;132,133,134;,
    3;135,136,137;,
    3;138,139,140;,
    3;141,142,143;,
    3;144,145,146;,
    3;147,148,149;,
    3;150,151,152;,
    3;153,154,155;,
    3;156,157,158;,
    3;159,160,161;,
    3;162,163,164;,
    3;165,166,167;,
    3;168,169,170;,
    3;171,172,173;,
    3;174,175,176;,
    3;177,178,179;,
    3;180,181,182;,
    3;183,184,185;,
    3;186,187,188;,
    3;189,190,191;;
   }

   MeshTextureCoords {
    192;
    1.623650;-3.129612;,
    2.669302;-2.866249;,
    -0.900783;-2.866249;,
    -0.301000;-0.750000;,
    -0.426000;-0.750000;,
    -0.426000;-0.999000;,
    -0.301000;-0.750000;,
    -0.426000;-0.999000;,
    -0.301000;-0.999000;,
    -4.470867;-2.898689;,
    -3.425215;-3.120285;,
    -0.900783;-2.898689;,
    -0.900783;-3.238700;,
    1.623650;-3.129612;,
    -0.900783;-2.866249;,
    -0.426000;-0.750000;,
    -0.486000;-0.750000;,
    -0.486000;-0.999000;,
    -0.426000;-0.750000;,
    -0.486000;-0.999000;,
    -0.426000;-0.999000;,
    -3.425215;-3.120285;,
    -0.900783;-3.212072;,
    -0.900783;-2.898689;,
    -3.425215;-3.129612;,
    -0.900783;-3.238700;,
    -0.900783;-2.866249;,
    -0.486000;-0.750000;,
    -0.553081;-0.750000;,
    -0.553081;-0.999000;,
    -0.486000;-0.750000;,
    -0.553081;-0.999000;,
    -0.486000;-0.999000;,
    -0.900783;-3.212072;,
    1.623650;-3.120285;,
    -0.900783;-2.898689;,
    -4.470867;-2.866249;,
    -3.425215;-3.129612;,
    -0.900783;-2.866249;,
    -0.553081;-0.750000;,
    -0.692000;-0.750000;,
    -0.692000;-0.999000;,
    -0.553081;-0.750000;,
    -0.692000;-0.999000;,
    -0.553081;-0.999000;,
    1.623650;-3.120285;,
    2.669302;-2.898689;,
    -0.900783;-2.898689;,
    -3.425215;-2.602884;,
    -4.470867;-2.866249;,
    -0.900783;-2.866249;,
    -0.692000;-0.750000;,
    -0.841000;-0.750000;,
    -0.841000;-0.999000;,
    -0.692000;-0.750000;,
    -0.841000;-0.999000;,
    -0.692000;-0.999000;,
    2.669302;-2.898689;,
    1.623650;-2.677089;,
    -0.900783;-2.898689;,
    -0.913042;-2.542878;,
    -3.425215;-2.602884;,
    -0.900783;-2.866249;,
    -0.841000;-0.750000;,
    -1.000000;-0.750000;,
    -1.000000;-0.999000;,
    -0.841000;-0.750000;,
    -1.000000;-0.999000;,
    -0.841000;-0.999000;,
    1.623650;-2.677089;,
    -0.900783;-2.585300;,
    -0.900783;-2.898689;,
    1.623650;-2.602884;,
    -0.913042;-2.542878;,
    -0.900783;-2.866249;,
    0.000000;-0.750000;,
    -0.142000;-0.750000;,
    -0.142000;-0.999000;,
    0.000000;-0.750000;,
    -0.142000;-0.999000;,
    0.000000;-0.999000;,
    -0.900783;-2.585300;,
    -3.425215;-2.677089;,
    -0.900783;-2.898689;,
    2.669302;-2.866249;,
    1.623650;-2.602884;,
    -0.900783;-2.866249;,
    -0.142000;-0.750000;,
    -0.301000;-0.750000;,
    -0.301000;-0.999000;,
    -0.142000;-0.750000;,
    -0.301000;-0.999000;,
    -0.142000;-0.999000;,
    -3.425215;-2.677089;,
    -4.470867;-2.898689;,
    -0.900783;-2.898689;,
    -0.692000;-0.999000;,
    -0.553081;-0.999000;,
    -0.553081;-0.750000;,
    -0.692000;-0.999000;,
    -0.553081;-0.750000;,
    -0.692000;-0.750000;,
    -0.553081;-0.999000;,
    -0.486000;-0.999000;,
    -0.486000;-0.750000;,
    -0.553081;-0.999000;,
    -0.486000;-0.750000;,
    -0.553081;-0.750000;,
    -0.486000;-0.999000;,
    -0.426000;-0.999000;,
    -0.426000;-0.750000;,
    -0.486000;-0.999000;,
    -0.426000;-0.750000;,
    -0.486000;-0.750000;,
    -0.426000;-0.999000;,
    -0.301000;-0.999000;,
    -0.301000;-0.750000;,
    -0.426000;-0.999000;,
    -0.301000;-0.750000;,
    -0.426000;-0.750000;,
    -0.301000;-0.999000;,
    -0.142000;-0.999000;,
    -0.142000;-0.750000;,
    -0.301000;-0.999000;,
    -0.142000;-0.750000;,
    -0.301000;-0.750000;,
    -0.142000;-0.999000;,
    0.000000;-0.999000;,
    0.000000;-0.750000;,
    -0.142000;-0.999000;,
    0.000000;-0.750000;,
    -0.142000;-0.750000;,
    -1.000000;-0.999000;,
    -0.841000;-0.999000;,
    -0.841000;-0.750000;,
    -1.000000;-0.999000;,
    -0.841000;-0.750000;,
    -1.000000;-0.750000;,
    -0.841000;-0.999000;,
    -0.692000;-0.999000;,
    -0.692000;-0.750000;,
    -0.841000;-0.999000;,
    -0.692000;-0.750000;,
    -0.841000;-0.750000;,
    -0.692000;-0.999000;,
    -0.554456;-0.999000;,
    -0.554456;-0.750000;,
    -0.692000;-0.999000;,
    -0.554456;-0.750000;,
    -0.692000;-0.750000;,
    -0.554456;-0.999000;,
    -0.486000;-0.999000;,
    -0.486000;-0.750000;,
    -0.554456;-0.999000;,
    -0.486000;-0.750000;,
    -0.554456;-0.750000;,
    -0.486000;-0.999000;,
    -0.426000;-0.999000;,
    -0.426000;-0.750000;,
    -0.486000;-0.999000;,
    -0.426000;-0.750000;,
    -0.486000;-0.750000;,
    -0.301000;-0.999000;,
    -0.301000;-0.999000;,
    -0.301000;-0.750000;,
    -0.301000;-0.999000;,
    -0.301000;-0.750000;,
    -0.301000;-0.750000;,
    -0.301000;-0.999000;,
    -0.142000;-0.999000;,
    -0.142000;-0.750000;,
    -0.301000;-0.999000;,
    -0.142000;-0.750000;,
    -0.301000;-0.750000;,
    -0.142000;-0.999000;,
    0.000000;-0.999000;,
    0.000000;-0.750000;,
    -0.142000;-0.999000;,
    0.000000;-0.750000;,
    -0.142000;-0.750000;,
    -1.000000;-0.999000;,
    -0.841000;-0.999000;,
    -0.841000;-0.750000;,
    -1.000000;-0.999000;,
    -0.841000;-0.750000;,
    -1.000000;-0.750000;,
    -0.841000;-0.999000;,
    -0.692000;-0.999000;,
    -0.692000;-0.750000;,
    -0.841000;-0.999000;,
    -0.692000;-0.750000;,
    -0.841000;-0.750000;;
   }

   MeshMaterialList {
    1;
    64;
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
    0,
    0;

    Material DefaultLib_Material10 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "reizouko.bmp";
     }
    }
   }
  }
 }
}