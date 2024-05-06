<br/>
<br/>


[English](README_EN.md)

<br />
<br />

如果您初次接触本项目，您可以：  
[查阅入门(快速上手)指南](https://www.easy-eai.com/document_details/3/133)

如果您具备丰富的嵌入式C语言开发经验，您可以：  
[直接先更新应用开发环境](https://www.easy-eai.com/document_details/3/135)  
[再查阅API开发手册](https://www.easy-eai.com/document_details/3/129)


使用方法：  
[1] - 克隆本GitHub仓库   
[2] - 进入具体的Demo目录执行：./build.sh    
[3] - 则会在具体的Demo目录的build/下生成相关的Demo：test-xxx

重要更新：
---
> 2024-05-06 : 
> * 发布 easyeai-c-demo-1.2.1
> * 更新 easyeai-api-1.2.18
>   * 算法组件
> 	  * [新增] BSD场景人员识别 Demo
> 	  * [更新] 骨骼点识别 Demo
> 	  * [更新] 车辆识别 Demo
> 	  * [更新] 二维码识别 Demo (增加条形码识别功能)
>   * 外设组件
> 	  * [更新] iic Demo
>
> 2024-01-18 : 
> * 发布 easyeai-c-demo-1.2.0
> * 更新 easyeai-api-1.2.10
>   * 多媒体组件
> 	  * [更新] 解码器&编码器 Demo
>   * 网络协议组件
> 	  * [更新] rtsp Demo
>   * 外设组件
> 	  * [更新] 摄像头 Demo
> 	  * [更新] 音频录音播放 Demo
>
> 2023-09-07 : 
> * 发布easyeai-c-demo-1.1.0
> * 更新 easyeai-api-1.1.0
>   * 算法组件
> 	  * [新增] OCR Demo
>   * 通用组件
> 	  * [新增] yaml操作 Demo
>   * 多媒体组件
> 	  * [更新] 解码器&编码器 Demo
>   * 外设组件
> 	  * [更新] GPIO Demo
> 	  * [更新] 看门狗 Demo
> 	  * [更新] 音频录音播放 Demo
>
> 2023-03-31 : 
> * 发布easyeai-c-demo-1.0.0
>   * 匹配 ubuntu 系统固件
>   * 匹配 easyeai-api v1.0.0
>   * 不兼容buildroot系统固件(buildroot版本的c-demo在本仓库的buildroot分支内)
>
> 2023-01-09 : 
> * 发布 easyeai-c-demo-0.2.2
> * 更新 easyeai-api-0.2.2
>   * 算法组件
> 	  * [新增] 人脸姿态估计Demo
> 	  * [更新] 人脸98点Demo
> 	  * [更新] 人脸识别Demo
>   * 多媒体组件
> 	  * [更新] 解码器&编码器 Demo
>   * 网络协议组件
> 	  * [更新] rtsp Demo
>   * 外设组件
> 	  * [新增] 网络配置 Demo
>
> 2022-11-24 : 
> * 更新 easyeai-c-demo-0.2.1
>   * 算法组件
> 	  * [新增] 口罩识别Demo
> * 更新 easyeai-api-0.2.1
>   * 算法组件
> 	  * [新增] 口罩识别
>
> 2022-11-19 : 
> * 更新 easyeai-c-demo-0.2.1
>   * 算法组件
> 	  * [新增] 移动监测 Demo
> 	  * [删除] 工地常见目标检测 Demo
>   * 外设组件
> 	  * [更新] 网络通信 TCP Demo
> 	  * [更新] 网络通信 UDP Demo
> * 更新 easyeai-api-0.2.1
>   * 算法组件
> 	  * [新增] 移动监测
> 	  * [更新] 火焰监测
>
> 2022-11-02 : 
> * 发布 easyeai-c-demo-0.2.1
> * 更新 easyeai-api-0.2.1
>   * 算法组件
> 	  * [新增] 人体骨骼点检测 Demo
> 	  * [新增] 火焰检测 Demo
> 	  * [新增] 工地常见目标检测 Demo
>   * 通用组件
> 	  * [新增] 进程间通信 Demo
> 	  * [更新] 字库引擎 Demo
>   * 媒体组件
> 	  * [新增] 编码器 Demo
>   * 网络协议组件
> 	  * [新增] rtsp Demo
>   * 外设组件
> 	  * [新增] can Demo
> 	  * [新增] iic Demo
> 	  * [新增] spi Demo
> 	  * [新增] 触摸屏 Demo
> 	  * [新增] 看门狗 Demo
> 	  * [更新] gpio Demo
>
> 2022-08-25 : 
> * 发布 easyeai-c-demo-0.2.0
> * 更新 easyeai-api-0.2.0
>   * 外设组件
> 	  * [新增] pwm Demo
> 	  * [更新] 摄像头 Demo
>   * 通用组件
> 	  * [更新] json格式处理 Demo
>
> 2022-05-25 : 
> * 发布 easyeai-c-demo-0.1.3
> * 更新 easyeai-api-0.1.3
>   * 算法组件
> 	  * [新增] 平面几何 Demo
> 	  * [新增] 安全帽检测 Demo
> 	  * [更新] 人脸检测 Demo
>   * 外设组件
> 	  * [更新] 显示控制 Demo
>   * 通用组件
> 	  * [更新] Linux系统设置 Demo
>   * 媒体组件
> 	  * [更新] 解码器 Demo
>
> 2022-04-13 : 
> * 发布 easyeai-c-demo-0.1.2
> * 更新 easyeai-api-0.1.2
>   * 算法组件
> 	  * [新增] 人脸检测 Demo
> 	  * [新增] 人脸识别 Demo
> 	  * [新增] 人员检测 Demo
> 	  * [新增] 自学习算法 Demo
>   * 外设组件
> 	  * [新增] gpio Demo
> 	  * [新增] 串口 Demo
> 	  * [新增] socketcan Demo
> 	  * [更新] wav录制和播放 Demo
> 	  * [更新] socket Demo
> 	  * [更新] 摄像头 Demo
>   * 媒体组件
> 	  * [更新] 解码器 Demo
>
> 2022-03-15 : 
> * 更新easyeai-api-0.1.1
>
> 2022-01-30 : 
> * 发布easyeai-c-demo-0.1.0
>   * 外设组件
> 	  * [新增] 音频播放 Demo
> 	  * [新增] 背光灯设置 Demo
> 	  * [新增] 显示控制 Demo
> 	  * [新增] 摄像头 Demo
> 	  * [新增] socket Demo
>   * 通用组件
> 	  * [新增] 字符串处理 Demo
> 	  * [新增] Linux系统设置 Demo
> 	  * [新增] base64转换 Demo
> 	  * [新增] 数据校验 Demo
> 	  * [新增] 二维码生成 Demo
> 	  * [新增] json格式处理 Demo
> 	  * [新增] ini文件处理 Demo
>   * 网络协议组件
> 	  * [新增] https Demo
> 	  * [新增] rtsp Demo
>   * 算法组件
> 	  * [新增] 二维码解码 Demo
>
> 2021-10-28 : 
> * 创建本项目
