//
//  Hitable.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/27/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

struct hit_record {
    var t: Float
    var p: vec3_extend
    var normal: vec3_extend
    var material: material?
    
    init() {
        t = 0.0
        p = vec3_extend()
        normal = vec3_extend()
    }
}

protocol hitable {
    func hit(_ r: ray, _ min: Float, _ max: Float, _ rec: inout hit_record) -> Bool
}
