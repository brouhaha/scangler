# Copyright 2023 Eric Smith
# SPDX-License-Identifier: GPL-3.0-only

import hashlib
import os
import uuid
from xml.dom import minidom

import SCons.Builder


def make_guid(s: str):
    m = hashlib.shake_128()
    m.update(s.encode('utf-8'))
    return str(uuid.UUID(m.hexdigest(16)))

def get_unique_tag(doc, tag):
    elems = doc.getElementsByTagName(tag)
    if len(elems) != 1:
        raise Exception(f'.xws template must have eactly one {tag} tag')
    return elems[0]

def get_tag_attr(doc, tag, attr, val):
    elems = doc.getElementsByTagName(tag)
    if len(elems) == 0:
        raise Exception(f'.xws template must have at least one {tag} tag')
    for elem in elems:
        if (elem.hasAttribute(attr) and
            (elem.getAttribute(attr) == val)):
            return elem
    raise Exception(f'.xws template has no {tag} tag with attr {attr} == {val}')
        

def insert_components(doc, paths):
    dir_app = get_tag_attr(doc, 'DirectoryRef', 'Id', 'INSTALLDIR')
    dir_qt_platforms = get_tag_attr(doc, 'DirectoryRef', 'Id', 'qt-platforms-dir')
    f = get_unique_tag(doc, 'Feature')

    for path in paths:
        base = os.path.basename(path)
        if base == 'qwindows.dll':
            dr = dir_qt_platforms
        else:
            dr = dir_app

        # instert Components into DirectoryRef
        e_comp = doc.createElement('Component')
        e_comp.setAttribute('Id', base)
        e_comp.setAttribute('Guid', make_guid(base))

        e_file = doc.createElement('File')
        e_file.setAttribute('Id', base)
        e_file.setAttribute('Name', base)
        e_file.setAttribute('DiskId', '1')
        e_file.setAttribute('Source', path)
        e_file.setAttribute('KeyPath', 'yes')

        e_comp.appendChild(e_file)
        dr.appendChild(e_comp)

        e_compref = doc.createElement('ComponentRef')
        e_compref.setAttribute('Id', base)
        f.appendChild(e_compref)

def parse_template(template):
    doc = minidom.parse(template)
    return doc

def write_wxs(doc, wxs):
    pretty = doc.toprettyxml(indent = '  ')

    result = ''
    for s in pretty.splitlines():
        s = s.rstrip()
        if len(s) != 0:
            result += s + '\n';

    wxs.write(result)



# the first file in source has to be the wxs template
# the remaining files are the components
def wxs_action(target, source, env):
    wxs_template = source[0].path
    files = [f.path for f in source[1:]]

    doc = parse_template(wxs_template)
    insert_components(doc, files)
    with open(target[0].path, 'w') as wxs:
        write_wxs(doc, wxs)


wxs_builder = SCons.Builder.Builder(action = wxs_action,
                                    suffix = '.wxs',
                                    src_suffix = '.wxst')

def generate(env, **kw):
    env.Append(BUILDERS = {'WXS': wxs_builder})

def exists(env):
    return True



import argparse
import sys



def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('template',
                        type = argparse.FileType('r'))
    parser.add_argument('wxs',
                        type = argparse.FileType('w'))
    args = parser.parse_args()

    doc = parse_template(args.template)

    insert_components(doc, ['../build/foo.bar', '../build/win32/voyager_lcd.exe'])

    write_wxs(doc, args.wxs)

if __name__ == '__main__':
    main()
