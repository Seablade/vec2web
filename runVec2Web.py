import os
path = '/x3ng/qcad2/vec2web/'
script = path + 'run_vec2web.sh'
arq_input = path + 'test/polyline.dxf'
arq_output = path + 'test/polyline.swf'
ret = os.strerror(os.spawnl(os.P_WAIT, script, script, arq_input, arq_output, '640', '480'))
print "Valor de retorno do os.spawnl:"
print ret
print "OK, vec2web works (from Python Script running from Shell)."
