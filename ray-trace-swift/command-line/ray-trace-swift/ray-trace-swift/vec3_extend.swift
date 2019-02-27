//
//  vec3_extend.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/26/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

struct vec3_extend {
    var f: [Float] = [0.0, 0.0, 0.0]
    var x: Float { return f[0] }
    var y: Float { return f[1] }
    var z: Float { return f[2] }
    var r: Float { return f[0] }
    var g: Float { return f[1] }
    var b: Float { return f[2] }
    var length: Float { return (f[0] * f[0] + f[1] * f[1] + f[2] * f[2]).squareRoot() }
    var length_squared: Float { return f[0] * f[0] + f[1] * f[1] + f[2] * f[2] }
    
    init() {}
    init(_ f_0: Float, _ f_1: Float, _ f_2: Float){
        f[0] = f_0
        f[1] = f_1
        f[2] = f_2
    }
    
    static prefix func + (vector: vec3_extend) -> vec3_extend { return vector }
    static prefix func - (vector: vec3_extend) -> vec3_extend {
        return vec3_extend(-vector.f[0], -vector.f[1], -vector.f[2])
    }
    subscript(index: Int) -> Float { return f[index] }
    
    public static func + (lhs: vec3_extend, rhs: vec3_extend) -> vec3_extend {
        return vec3_extend(lhs.f[0] + rhs.f[0], lhs.f[1] + rhs.f[1], lhs.f[2] + rhs.f[2])
    }
    public static func - (lhs: vec3_extend, rhs: vec3_extend) -> vec3_extend {
        return vec3_extend(lhs.f[0] - rhs.f[0], lhs.f[1] - rhs.f[1], lhs.f[2] - rhs.f[2])
    }
    public static func * (lhs: vec3_extend, rhs: vec3_extend) -> vec3_extend {
        return vec3_extend(lhs.f[0] * rhs.f[0], lhs.f[1] * rhs.f[1], lhs.f[2] * rhs.f[2])
    }
    public static func / (lhs: vec3_extend, rhs: vec3_extend) -> vec3_extend {
        return vec3_extend(lhs.f[0] / rhs.f[0], lhs.f[1] / rhs.f[1], lhs.f[2] / rhs.f[2])
    }
    public static func * (lhs: vec3_extend, c: Float) -> vec3_extend {
        return vec3_extend(lhs.f[0] * c, lhs.f[1] * c, lhs.f[2] * c)
    }
    public static func / (lhs: vec3_extend, c: Float) -> vec3_extend {
        return vec3_extend(lhs.f[0] / c, lhs.f[1] / c, lhs.f[2] / c)
    }
    
    public static func += (lhs: inout vec3_extend, rhs: vec3_extend) { lhs = lhs + rhs }
    public static func -= (lhs: inout vec3_extend, rhs: vec3_extend) { lhs = lhs + rhs }
    public static func *= (lhs: inout vec3_extend, rhs: vec3_extend) { lhs = lhs * rhs }
    public static func /= (lhs: inout vec3_extend, rhs: vec3_extend) { lhs = lhs / rhs }
    public static func *= (lhs: inout vec3_extend, c: Float) { lhs = lhs * c }
    public static func /= (lhs: inout vec3_extend, c: Float) { lhs = lhs / c }
    
    mutating func unit_vector() {
        let k = 1.0 / length
        self *= k
    }
}

func unit_vector(vector: vec3_extend) -> vec3_extend {
    return vector / vector.length
}

func dot_product(_ vector1: vec3_extend, _ vector2: vec3_extend) -> Float {
    return vector1.f[0] * vector2.f[0]
        + vector1.f[1] * vector2.f[1]
        +  vector1.f[2] * vector2.f[2]
}

func cross_product(_ vector1: vec3_extend, _ vector2: vec3_extend) -> vec3_extend {
    return vec3_extend(vector1.f[1]*vector2.f[2] - vector1.f[2]*vector2.f[1],
                       -(vector1.f[0]*vector2.f[2] - vector1.f[2]*vector2.f[0]),
                       vector1.f[0]*vector2.f[1] - vector1.f[1]*vector2.f[0])
}

extension Float {
    static func * (c: Float, rhs: vec3_extend) -> vec3_extend {
        return rhs * c
    }
}
