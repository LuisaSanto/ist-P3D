//
//  Ray.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/26/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

struct ray {
    var o: vec3_extend
    var d: vec3_extend
    
    init() { self.init(vec3_extend(), vec3_extend()) }
    init(_ o: vec3_extend, _ d: vec3_extend) {
        self.o = o
        self.d = d
    }
    
    var origin: vec3_extend { return o }
    var direction: vec3_extend { return d }
    func pointAtParameter(_ t: Float) -> vec3_extend {
        return o + t*d
    }
    
}
