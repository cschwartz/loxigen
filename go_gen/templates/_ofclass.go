type ${ofclass.pyname} struct {
:: for m in ofclass.members:
::   if not (m.__class__.__name__  in ['OFPadMember'] or  m.name in ['version', 'type', 'length', 'xid']):
::     if not m.oftype.startswith('list'):
::       if m.base_length != 0 :
  ${m.name} ${type_for_field(ofclass, m)}
::       else:
  ${m.name} []byte
::       #endif
::     #endif
::   #endif
:: #endfor
}

func (m *${ofclass.pyname}) parse(data []byte) {
:: for m in ofclass.members:
::   if not (m.__class__.__name__  in ['OFPadMember'] or  m.name in ['version', 'type', 'length', 'xid']):
::     if not m.oftype.startswith('list') and m.offset:
::       if m.base_length != 0 :
  binary.Read(bytes.NewReader(data[${m.offset}:${m.offset + m.base_length}]), binary.BigEndian, &m.${m.name})
::       else:
  binary.Read(bytes.NewReader(data[${m.offset}:len(data)]), binary.BigEndian, &m.${m.name})
::       #endif
::     else:
// ignore ${m.name} for the moment
::     #endif
::   #endif
:: #endfor
}

func (m ${ofclass.pyname}) fillOutEvent(event *common.MapStr) {
:: for m in ofclass.members:
::   if not (m.__class__.__name__  in ['OFPadMember'] or  m.name in ['version', 'type', 'length', 'xid']):
::     if not m.oftype.startswith('list'):
::       if m.base_length != 0:
::          if type_for_field(ofclass, m) in enums and len(enums[type_for_field(ofclass, m)].values) > 0:
  (*event)["${m.name}"] = m.${m.name}.String()
::          else:
  (*event)["${m.name}"] = m.${m.name}
::          #endif
::       #endif
::     else:
  // ignore ${m.name} for the moment
::     #endif
::   #endif
:: #endfor
}
