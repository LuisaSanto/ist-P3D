//
//  Material.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/27/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

protocol material {
    func scatter(_ ray_in: ray, _ rec: hit_record, attenuation: inout vec3_extend, scaterred: inout ray) -> Bool
}
