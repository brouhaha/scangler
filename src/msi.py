# Copyright 2023 Eric Smith
# SPDX-License-Identifier: GPL-3.0-only

import SCons.Builder

msi_builder = SCons.Builder.Builder(action = 'wixl $SOURCE',
                                    suffix = '.msi',
                                    src_suffix = '.wxs')

def generate(env, **kw):
    env.Append(BUILDERS = {'MSI': msi_builder})

def exists(env):
    return True
