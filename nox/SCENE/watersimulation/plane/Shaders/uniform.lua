setUniform1f("time",os.clock()*9)
setUniform1f("speed",0.3)
setUniform1f("randX",0.1)
setUniform1f("randY",0.1)

setUniform3f("lightPosition",1.0,1.0,20.0)
setUniform3f("lightColor",1.0,1.0,1.0)
setUniform3f("waterColor",0.023,0.258,0.450)
setCameraToShader("cameraPosition")
