:: # Copyright 2013, Big Switch Networks, Inc.
:: #
:: # LoxiGen is licensed under the Eclipse Public License, version 1.0 (EPL), with
:: # the following special exception:
:: #
:: # LOXI Exception
:: #
:: # As a special exception to the terms of the EPL, you may distribute libraries
:: # generated by LoxiGen (LoxiGen Libraries) under the terms of your choice, provided
:: # that copyright and licensing notices generated by LoxiGen are not altered or removed
:: # from the LoxiGen Libraries and the notice provided below is (i) included in
:: # the LoxiGen Libraries, if distributed in source code form and (ii) included in any
:: # documentation for the LoxiGen Libraries, if distributed in binary form.
:: #
:: # Notice: "Copyright 2013, Big Switch Networks, Inc. This library was generated by the LoxiGen Compiler."
:: #
:: # You may not use this file except in compliance with the EPL or LOXI Exception. You may obtain
:: # a copy of the EPL at:
:: #
:: # http://www.eclipse.org/legal/epl-v10.html
:: #
:: # Unless required by applicable law or agreed to in writing, software
:: # distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
:: # WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
:: # EPL for the specific language governing permissions and limitations
:: # under the EPL.
::
void
${data.class_name}_wire_object_id_get(of_object_t *obj, of_object_id_t *id)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
:: for version, version_data in data.versioned:
    case ${version.constant_version(prefix='OF_VERSION_')}: {
:: m = version_data.discriminator
:: if m.length == 1:
        uint8_t value = *(uint8_t *)(buf + ${m.offset}); /* ${m.name} */
:: elif m.length == 2:
        uint16_t value = U16_NTOH(*(uint16_t *)(buf + ${m.offset})); /* ${m.name} */
:: elif m.length == 4:
        uint32_t value = U32_NTOH(*(uint32_t *)(buf + ${m.offset})); /* ${m.name} */
:: elif m.length == 8:
        uint64_t value = U64_NTOH(*(uint64_t *)(buf + ${m.offset})); /* ${m.name} */
:: else:
:: raise("unsupported parse_wire_types length %d" % m.length)
:: #endif
::
        switch (value) {
:: for subclass in version_data.subclasses:
        case ${hex(subclass.value)}:
:: if subclass.virtual:
            ${subclass.class_name}_wire_object_id_get(obj, id);
:: else:
            *id = ${subclass.class_name.upper()};
:: #endif
            break;
:: #endfor
        default:
            *id = ${data.class_name.upper()};
            break;
        }
        break;
    }
:: #endfor
    default:
        LOCI_ASSERT(0);
    }
}