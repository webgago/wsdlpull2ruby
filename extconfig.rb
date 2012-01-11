require "mkmf"

$CPPFLAGS << " -I%s" % ["/usr/local/include/wsdlpull"]

LIBDIR = RbConfig::CONFIG['libdir']
LIB_DIRS = ['/opt/local/lib', '/usr/local/lib', LIBDIR, '/usr/lib', '/usr/local/lib/wsdlpull']


dir_config('wsdlpull', ['/usr/local/include/wsdlpull'], ['/usr/local/lib/wsdlpull'])

find_library('wsdlpull', 'SchemaParser')
$libs = append_library($libs, 'wsdlpull')
$libs = append_library($libs, 'wsdlpullschema')
$libs = append_library($libs, 'wsdlpullxml')
create_makefile('test/foo', 'test')