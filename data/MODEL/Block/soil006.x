xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 500;
 -20.00000;20.00000;-20.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 20.00000;-20.00000;-20.00000;,
 20.00000;20.00000;20.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 -20.00000;-20.00000;20.00000;,
 20.00000;20.00000;-20.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 20.00000;20.00000;-20.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 60.00000;-20.00000;-20.00000;,
 60.00000;20.00000;20.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 20.00000;-20.00000;20.00000;,
 60.00000;20.00000;-20.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 60.00000;20.00000;-20.00000;,
 100.00000;20.00000;-20.00000;,
 100.00000;-20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 100.00000;20.00000;-20.00000;,
 100.00000;20.00000;20.00000;,
 100.00000;-20.00000;20.00000;,
 100.00000;-20.00000;-20.00000;,
 100.00000;20.00000;20.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 100.00000;-20.00000;20.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 60.00000;-20.00000;20.00000;,
 100.00000;20.00000;-20.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 100.00000;-20.00000;-20.00000;,
 -60.00000;20.00000;-20.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 -20.00000;-20.00000;-20.00000;,
 -20.00000;20.00000;20.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -60.00000;-20.00000;20.00000;,
 -20.00000;20.00000;-20.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 -100.00000;20.00000;-20.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -100.00000;-20.00000;-20.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -60.00000;20.00000;20.00000;,
 -100.00000;20.00000;20.00000;,
 -100.00000;-20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -100.00000;20.00000;20.00000;,
 -100.00000;20.00000;-20.00000;,
 -100.00000;-20.00000;-20.00000;,
 -100.00000;-20.00000;20.00000;,
 -60.00000;20.00000;-20.00000;,
 -100.00000;20.00000;-20.00000;,
 -100.00000;-20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -20.00000;20.00000;-60.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 20.00000;-20.00000;-60.00000;,
 20.00000;20.00000;-20.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 -20.00000;-20.00000;-20.00000;,
 20.00000;20.00000;-60.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 20.00000;20.00000;-60.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 60.00000;-20.00000;-60.00000;,
 60.00000;20.00000;-20.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;-20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 20.00000;20.00000;-20.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 20.00000;-20.00000;-20.00000;,
 60.00000;20.00000;-60.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 60.00000;20.00000;-60.00000;,
 100.00000;20.00000;-60.00000;,
 100.00000;-20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 100.00000;20.00000;-60.00000;,
 100.00000;20.00000;-20.00000;,
 100.00000;-20.00000;-20.00000;,
 100.00000;-20.00000;-60.00000;,
 100.00000;20.00000;-20.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;-20.00000;-20.00000;,
 100.00000;-20.00000;-20.00000;,
 60.00000;20.00000;-20.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 60.00000;-20.00000;-20.00000;,
 100.00000;20.00000;-60.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 100.00000;-20.00000;-60.00000;,
 -60.00000;20.00000;-60.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 -20.00000;-20.00000;-60.00000;,
 -20.00000;20.00000;-20.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -20.00000;-20.00000;-20.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -60.00000;-20.00000;-20.00000;,
 -20.00000;20.00000;-60.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 -100.00000;20.00000;-60.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -100.00000;-20.00000;-60.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -60.00000;-20.00000;-60.00000;,
 -60.00000;20.00000;-20.00000;,
 -100.00000;20.00000;-20.00000;,
 -100.00000;-20.00000;-20.00000;,
 -60.00000;-20.00000;-20.00000;,
 -100.00000;20.00000;-20.00000;,
 -100.00000;20.00000;-60.00000;,
 -100.00000;-20.00000;-60.00000;,
 -100.00000;-20.00000;-20.00000;,
 -60.00000;20.00000;-60.00000;,
 -100.00000;20.00000;-60.00000;,
 -100.00000;-20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -20.00000;20.00000;-100.00000;,
 20.00000;20.00000;-100.00000;,
 20.00000;-20.00000;-100.00000;,
 -20.00000;-20.00000;-100.00000;,
 20.00000;20.00000;-100.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 20.00000;-20.00000;-100.00000;,
 20.00000;20.00000;-60.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;20.00000;-100.00000;,
 -20.00000;-20.00000;-100.00000;,
 -20.00000;-20.00000;-60.00000;,
 20.00000;20.00000;-100.00000;,
 -20.00000;20.00000;-100.00000;,
 -20.00000;-20.00000;-100.00000;,
 20.00000;-20.00000;-100.00000;,
 20.00000;20.00000;-100.00000;,
 60.00000;20.00000;-100.00000;,
 60.00000;-20.00000;-100.00000;,
 20.00000;-20.00000;-100.00000;,
 60.00000;20.00000;-100.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 60.00000;-20.00000;-100.00000;,
 60.00000;20.00000;-60.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;-20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 20.00000;20.00000;-60.00000;,
 20.00000;20.00000;-100.00000;,
 20.00000;-20.00000;-100.00000;,
 20.00000;-20.00000;-60.00000;,
 60.00000;20.00000;-100.00000;,
 20.00000;20.00000;-100.00000;,
 20.00000;-20.00000;-100.00000;,
 60.00000;-20.00000;-100.00000;,
 60.00000;20.00000;-100.00000;,
 100.00000;20.00000;-100.00000;,
 100.00000;-20.00000;-100.00000;,
 60.00000;-20.00000;-100.00000;,
 100.00000;20.00000;-100.00000;,
 100.00000;20.00000;-60.00000;,
 100.00000;-20.00000;-60.00000;,
 100.00000;-20.00000;-100.00000;,
 100.00000;20.00000;-60.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;-20.00000;-60.00000;,
 100.00000;-20.00000;-60.00000;,
 60.00000;20.00000;-60.00000;,
 60.00000;20.00000;-100.00000;,
 60.00000;-20.00000;-100.00000;,
 60.00000;-20.00000;-60.00000;,
 100.00000;20.00000;-100.00000;,
 60.00000;20.00000;-100.00000;,
 60.00000;-20.00000;-100.00000;,
 100.00000;-20.00000;-100.00000;,
 -60.00000;20.00000;-100.00000;,
 -20.00000;20.00000;-100.00000;,
 -20.00000;-20.00000;-100.00000;,
 -60.00000;-20.00000;-100.00000;,
 -20.00000;20.00000;-100.00000;,
 -20.00000;20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 -20.00000;-20.00000;-100.00000;,
 -20.00000;20.00000;-60.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -20.00000;-20.00000;-60.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;20.00000;-100.00000;,
 -60.00000;-20.00000;-100.00000;,
 -60.00000;-20.00000;-60.00000;,
 -20.00000;20.00000;-100.00000;,
 -60.00000;20.00000;-100.00000;,
 -60.00000;-20.00000;-100.00000;,
 -20.00000;-20.00000;-100.00000;,
 -100.00000;20.00000;-100.00000;,
 -60.00000;20.00000;-100.00000;,
 -60.00000;-20.00000;-100.00000;,
 -100.00000;-20.00000;-100.00000;,
 -60.00000;20.00000;-100.00000;,
 -60.00000;20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -60.00000;-20.00000;-100.00000;,
 -60.00000;20.00000;-60.00000;,
 -100.00000;20.00000;-60.00000;,
 -100.00000;-20.00000;-60.00000;,
 -60.00000;-20.00000;-60.00000;,
 -100.00000;20.00000;-60.00000;,
 -100.00000;20.00000;-100.00000;,
 -100.00000;-20.00000;-100.00000;,
 -100.00000;-20.00000;-60.00000;,
 -60.00000;20.00000;-100.00000;,
 -100.00000;20.00000;-100.00000;,
 -100.00000;-20.00000;-100.00000;,
 -60.00000;-20.00000;-100.00000;,
 -20.00000;20.00000;20.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 20.00000;-20.00000;20.00000;,
 20.00000;20.00000;60.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 -20.00000;-20.00000;60.00000;,
 20.00000;20.00000;20.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 20.00000;20.00000;20.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 60.00000;-20.00000;20.00000;,
 60.00000;20.00000;60.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 20.00000;-20.00000;60.00000;,
 60.00000;20.00000;20.00000;,
 20.00000;20.00000;20.00000;,
 20.00000;-20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 60.00000;20.00000;20.00000;,
 100.00000;20.00000;20.00000;,
 100.00000;-20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 100.00000;20.00000;20.00000;,
 100.00000;20.00000;60.00000;,
 100.00000;-20.00000;60.00000;,
 100.00000;-20.00000;20.00000;,
 100.00000;20.00000;60.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 100.00000;-20.00000;60.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 60.00000;-20.00000;60.00000;,
 100.00000;20.00000;20.00000;,
 60.00000;20.00000;20.00000;,
 60.00000;-20.00000;20.00000;,
 100.00000;-20.00000;20.00000;,
 -60.00000;20.00000;20.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -20.00000;20.00000;20.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 -20.00000;-20.00000;20.00000;,
 -20.00000;20.00000;60.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -60.00000;-20.00000;60.00000;,
 -20.00000;20.00000;20.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -20.00000;-20.00000;20.00000;,
 -100.00000;20.00000;20.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -100.00000;-20.00000;20.00000;,
 -60.00000;20.00000;20.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -60.00000;-20.00000;20.00000;,
 -60.00000;20.00000;60.00000;,
 -100.00000;20.00000;60.00000;,
 -100.00000;-20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -100.00000;20.00000;60.00000;,
 -100.00000;20.00000;20.00000;,
 -100.00000;-20.00000;20.00000;,
 -100.00000;-20.00000;60.00000;,
 -60.00000;20.00000;20.00000;,
 -100.00000;20.00000;20.00000;,
 -100.00000;-20.00000;20.00000;,
 -60.00000;-20.00000;20.00000;,
 -20.00000;20.00000;60.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;20.00000;100.00000;,
 20.00000;-20.00000;100.00000;,
 20.00000;-20.00000;60.00000;,
 20.00000;20.00000;100.00000;,
 -20.00000;20.00000;100.00000;,
 -20.00000;-20.00000;100.00000;,
 20.00000;-20.00000;100.00000;,
 -20.00000;20.00000;100.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 -20.00000;-20.00000;100.00000;,
 20.00000;20.00000;60.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 20.00000;20.00000;60.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;20.00000;100.00000;,
 60.00000;-20.00000;100.00000;,
 60.00000;-20.00000;60.00000;,
 60.00000;20.00000;100.00000;,
 20.00000;20.00000;100.00000;,
 20.00000;-20.00000;100.00000;,
 60.00000;-20.00000;100.00000;,
 20.00000;20.00000;100.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 20.00000;-20.00000;100.00000;,
 60.00000;20.00000;60.00000;,
 20.00000;20.00000;60.00000;,
 20.00000;-20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 60.00000;20.00000;60.00000;,
 100.00000;20.00000;60.00000;,
 100.00000;-20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 100.00000;20.00000;60.00000;,
 100.00000;20.00000;100.00000;,
 100.00000;-20.00000;100.00000;,
 100.00000;-20.00000;60.00000;,
 100.00000;20.00000;100.00000;,
 60.00000;20.00000;100.00000;,
 60.00000;-20.00000;100.00000;,
 100.00000;-20.00000;100.00000;,
 60.00000;20.00000;100.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 60.00000;-20.00000;100.00000;,
 100.00000;20.00000;60.00000;,
 60.00000;20.00000;60.00000;,
 60.00000;-20.00000;60.00000;,
 100.00000;-20.00000;60.00000;,
 -60.00000;20.00000;60.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -20.00000;20.00000;60.00000;,
 -20.00000;20.00000;100.00000;,
 -20.00000;-20.00000;100.00000;,
 -20.00000;-20.00000;60.00000;,
 -20.00000;20.00000;100.00000;,
 -60.00000;20.00000;100.00000;,
 -60.00000;-20.00000;100.00000;,
 -20.00000;-20.00000;100.00000;,
 -60.00000;20.00000;100.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -60.00000;-20.00000;100.00000;,
 -20.00000;20.00000;60.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -20.00000;-20.00000;60.00000;,
 -100.00000;20.00000;60.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;,
 -100.00000;-20.00000;60.00000;,
 -60.00000;20.00000;60.00000;,
 -60.00000;20.00000;100.00000;,
 -60.00000;-20.00000;100.00000;,
 -60.00000;-20.00000;60.00000;,
 -60.00000;20.00000;100.00000;,
 -100.00000;20.00000;100.00000;,
 -100.00000;-20.00000;100.00000;,
 -60.00000;-20.00000;100.00000;,
 -100.00000;20.00000;100.00000;,
 -100.00000;20.00000;60.00000;,
 -100.00000;-20.00000;60.00000;,
 -100.00000;-20.00000;100.00000;,
 -60.00000;20.00000;60.00000;,
 -100.00000;20.00000;60.00000;,
 -100.00000;-20.00000;60.00000;,
 -60.00000;-20.00000;60.00000;;
 
 150;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,225,236,237;,
 4;238,239,226,235;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;252,245,256,257;,
 4;258,259,246,255;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;272,265,276,277;,
 4;278,279,266,275;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;292,285,296,297;,
 4;298,299,286,295;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;312,305,316,317;,
 4;318,319,306,315;,
 4;320,321,322,323;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;332,325,336,337;,
 4;338,339,326,335;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;352,345,356,357;,
 4;358,359,346,355;,
 4;360,361,362,363;,
 4;364,365,366,367;,
 4;368,369,370,371;,
 4;372,373,374,375;,
 4;372,365,376,377;,
 4;378,379,366,375;,
 4;380,381,382,383;,
 4;384,385,386,387;,
 4;388,389,390,391;,
 4;392,393,394,395;,
 4;392,385,396,397;,
 4;398,399,386,395;,
 4;400,401,402,403;,
 4;404,405,406,407;,
 4;408,409,410,411;,
 4;412,413,414,415;,
 4;412,405,416,417;,
 4;418,419,406,415;,
 4;420,421,422,423;,
 4;424,425,426,427;,
 4;428,429,430,431;,
 4;432,433,434,435;,
 4;432,425,436,437;,
 4;438,439,426,435;,
 4;440,441,442,443;,
 4;444,445,446,447;,
 4;448,449,450,451;,
 4;452,453,454,455;,
 4;452,445,456,457;,
 4;458,459,446,455;,
 4;460,461,462,463;,
 4;464,465,466,467;,
 4;468,469,470,471;,
 4;472,473,474,475;,
 4;472,465,476,477;,
 4;478,479,466,475;,
 4;480,481,482,483;,
 4;484,485,486,487;,
 4;488,489,490,491;,
 4;492,493,494,495;,
 4;492,485,496,497;,
 4;498,499,486,495;;
 
 MeshMaterialList {
  1;
  150;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\GrassBlock02.png";
   }
  }
 }
 MeshNormals {
  30;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  150;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;;
 }
 MeshTextureCoords {
  500;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
