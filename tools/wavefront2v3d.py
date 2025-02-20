#!/usr/bin/env python3
#
# Wavefront to Varooom Converter
# Copyright 2024 Nikku4211
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty
# provided the copyright notice and this notice are preserved.
# This file is offered as-is, without any warranty.
#
import os
import sys
import math
from random import randrange

#thanks gvaliente
def sub(a, b):
    result = []

    for i in range(len(a)):
        result.append(a[i] - b[i])

    return result


def cross(a, b):
    return [a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0]]


def norm(v):
    return math.sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]))


def normal(p0, p1, p2):
    # cross_product = np.cross(p1 - p0, p2 - p0)
    cross_product = cross(sub(p1, p0), sub(p2, p0))
    # normal = cross_product / np.linalg.norm(cross_product)
    magnitude = norm(cross_product)
    return [cross_product[0] / magnitude, cross_product[1] / magnitude, cross_product[2] / magnitude]


def main(argv):
    #handle arguments and help
    if len(argv) >= 2 and argv[1] in ('--help', '-h'):
        print('usage: objinput v3doutput modelname modelscale --recalcnorms')
        sys.exit(1)
    elif len(argv) < 4:
        print('too few arguments, need --help?')
        sys.exit(1)

    #recalculating vertex normals is optional
    recalcvertexnorms = True if len(argv) >= 6 and argv[5] in ('-rn', '--recalcnorms') else False
    waveobjfile = open(argv[1],"rt")
    waveobjdata = waveobjfile.readlines()

    wavemtlfilename = []

    #get material file from obj file
    for x in range(len(waveobjdata)):
        if waveobjdata[x][0:7] == "mtllib ":
            wavemtlfilename = os.path.dirname(os.path.abspath(argv[1])) + "/" + waveobjdata[x][7:-1]

    wavemtlfile = open(wavemtlfilename,"rt")
    wavemtldata = wavemtlfile.readlines()

    #wavefront variables
    wavevertices = []
    wavevertexnorms = []
    wavefacels = []
    wavecolours = []
    wavematerialcurrent = -1
    wavematerialindices = []
    wavematerialnames = []

    v3dfile = open(argv[2], 'wt')

    modelname = argv[3]

    modelscale = float(argv[4])

    v3dfile.write("""
    /*
     * Generated by Nikku4211's Wavefront to Varooom Converter
     * Nikku4211 - github.com/nikku4211/
     *
     */

    #ifndef FR_MODEL_3D_ITEMS_%s_H
    #define FR_MODEL_3D_ITEMS_%s_H

    #include "fr_model_3d_item.h"

    namespace fr::model_3d_items
    {
        constexpr inline vertex_3d %s_vertices[] = {\n""" % (modelname,modelname,modelname))

    #read vertices as specified in the obj file and then scale them
    for x in range(len(waveobjdata)):
        if waveobjdata[x][0:2] == "v ":
            waveverticesub = []
            for i in range(len(waveobjdata[x][2::].split())):
                waveverticesub.append(float(waveobjdata[x][2::].split()[i])*modelscale)
            wavevertices.append(waveverticesub)
            v3dfile.write('             vertex_3d('
            + "".join('%s' % str(float(waveobjdata[x][2::].split()[0])*modelscale))
            + ","
            + "".join('%s' % str(float(waveobjdata[x][2::].split()[1])*modelscale))
            + ","
            + "".join('%s' % str(float(waveobjdata[x][2::].split()[2])*modelscale))
            + '),\n'
            )


    v3dfile.write("""       };\n""")

    v3dfile.write("    constexpr inline bn::color %s_colors[] = {\n" % modelname)

    #convert floating point rgb components specified in obj to 5-bit integers
    for x in range(len(wavemtldata)):
        if wavemtldata[x][0:3] == "Kd ":
            if wavemtldata[x][3::] not in wavecolours:
                wavecolours.append(wavemtldata[x][3::])
                v3dfile.write('             bn::color('
                + "".join('%s' % math.floor(float(wavemtldata[x][3::].split()[0])*31))
                + ","
                + "".join('%s' % math.floor(float(wavemtldata[x][3::].split()[1])*31))
                + ","
                + "".join('%s' % math.floor(float(wavemtldata[x][3::].split()[2])*31))
                + '),\n'
                )
            wavematerialnames.append(wavemtldata[x-3][7::])
            wavematerialnames.append(wavemtldata[x][3::])
    # print("materials test")
    # print(wavematerialnames)

    v3dfile.write("    };\n")

    #give these colours names
    for x in range(len(wavecolours)):
        v3dfile.write('    constexpr inline int %s_color_%d = ' % (modelname, x)
        + "".join('%d' % x)
        + ";\n"
        )

    v3dfile.write("""
    constexpr inline face_3d %s_faces_full[] = {\n""" % (modelname))

    #if we're not recalculating the vertex normals, take them as specified in the obj
    #and in either case, take the face vertex indices as specified in the obj
    for x in range(len(waveobjdata)):
        # print(waveobjdata[x])
        if waveobjdata[x][0:3] == "vn " and recalcvertexnorms == False:
            wavevertexnormssub = []
            for i in range(len(waveobjdata[x][3::].split())):
                wavevertexnormssub.append(waveobjdata[x][3::].split()[i])
            wavevertexnorms.append(wavevertexnormssub)
        elif waveobjdata[x][0:2] == "f ":
            wavefacelnormindices = []
            for i in range(len(waveobjdata[x][2::].split())):
                if waveobjdata[x][2::].find('/'):
                    wavefacelnormindices.append(str(int(waveobjdata[x][2::].split()[i].split("/")[0])-1))
                else:
                    wavefacelnormindices.append(str(int(waveobjdata[x][2::].split()[i])-1))
            wavefacels.append(wavefacelnormindices)
            wavematerialindices.append(max(0, wavematerialcurrent))
        elif waveobjdata[x][0:7] == "usemtl ":
            if wavematerialnames[wavematerialnames.index(waveobjdata[x][7::])] not in wavematerialnames[:(wavematerialnames.index(waveobjdata[x][7::]))]:
                wavematerialcurrent += 1

    # print ("wavefacels ("+ str(len(wavefacels)) +"): " + str(wavefacels))
    # print ("wavematerialindices ("+ str(len(wavematerialindices)) +"): " + str(wavematerialindices))

    #if we're recalculating the vertex normals, take the sum of the cross product of all the vertices
    if recalcvertexnorms == True:
        for x in range(len(wavefacels)):
            p0 = wavevertices[int(wavefacels[x][0])]
            p1 = wavevertices[int(wavefacels[x][1])] 
            p2 = wavevertices[int(wavefacels[x][2])]
            # print(wavevertices[int(wavefacels[x][0])])
            # print(wavevertices[int(wavefacels[x][1])])
            # print(wavevertices[int(wavefacels[x][2])])
            wavevertexnormssub = normal(p0, p1, p2)
            wavevertexnorms.append(wavevertexnormssub)
            # print(wavevertexnorms[x])

    # print ("wavevertexnorms ("+ str(len(wavevertexnorms)) +"): " + str(wavevertexnorms))

    if (recalcvertexnorms == False and len(wavevertexnorms) != len(wavefacels)):
        print ("ERROR: Normals list doesn't match faces list sizing. Please use --recalcnorms parameter.")
        return

    #then put all the vertex normals, face indices, and material indices together in the v3d header file
    for x in range(len(wavevertexnorms)):
        v3dfile.write('        face_3d(%s_vertices, vertex_3d(' % modelname
        + "".join("%s" % wavevertexnorms[x][0])
        + ","
        + "".join("%s" % wavevertexnorms[x][1])
        + ","
        + "".join("%s" % wavevertexnorms[x][2])
        + "),"
        + ",".join(wavefacels[x])
        + ","
        + "".join("%d" % wavematerialindices[x])
        + ','
        + "".join("%d" % randrange(8)) #"7"
        + '),\n'
        )

    v3dfile.write("""    };\n""")
    v3dfile.write("""    constexpr inline model_3d_item %s_full(%s_vertices, %s_faces_full, %s_colors);\n""" % (modelname,modelname,modelname,modelname))
    v3dfile.write("""    };\n""")
    v3dfile.write("#endif")

if __name__=='__main__':
    main(sys.argv)