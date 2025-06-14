# Virtual Protocol Adapter (VPA) RPC Framework

**daphne.goodall.com:/home/devo/public_html/fw/README.md**  
**Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.**  
**Version: 5.5.10.2**  
**Last Updated: 2025/02/19**

---

## Table of Contents

1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Framework Components](#framework-components)
4. [Installation & Setup](#installation--setup)
5. [RPC System](#rpc-system)
6. [Development Environment](#development-environment)
7. [API Reference](#api-reference)
8. [Deployment Guide](#deployment-guide)
9. [Performance & Monitoring](#performance--monitoring)
10. [Troubleshooting](#troubleshooting)
11. [Contributing](#contributing)
12. [License](#license)

---

## Overview

The Virtual Protocol Adapter (VPA) RPC Framework is a comprehensive C++20-based middleware system designed for building distributed applications with remote procedure call capabilities. The framework provides a robust foundation for client-server communication, featuring visual status monitoring, semi-graphics user interfaces, and enterprise-grade reliability.

### Key Features

- **🚀 High-Performance RPC**: TCP/IP based remote procedure calls with minimal latency
- **🎨 Visual Interface**: Real-time status monitoring with customizable semi-graphics styling
- **🔧 Modular Architecture**: Component-based design with dependency injection
- **🌐 Cross-Platform**: Linux/Unix compatible with portable C++20 implementation
- **📊 Built-in Monitoring**: Visual feedback for all network operations and system status
- **🔒 Enterprise Ready**: Comprehensive logging, error handling, and resource management

### Framework Philosophy

The framework design emphasizes practical functionality over theoretical purity. While global pointers are generally discouraged in modern C++, this framework strategically employs them for accessing stateless services, providing a clean API for distributed system development. The architecture balances performance, maintainability, and developer experience.

---

## Architecture

### System Overview

### Design Patterns

- **Middleware Pattern**: mwfw2 provides cross-cutting concerns
- **Service Locator**: Global pointers for framework services
- **Template Method**: Extensible RPC command processing
- **Observer Pattern**: Real-time UI updates for network events
- **Factory Pattern**: Dynamic object creation and lifecycle management

---

## Framework Components

### Core Libraries

#### 1. mwfw2 Middleware Framework
```cpp
// Primary system initialization and service management
mwfw2 * pMwFw = new mwfw2(__FILE__, __FUNCTION__);
```

// Main RPC implementation class
class vparpc {
public:
    void server(std::string ssService);
    void client(std::string ssHostName, std::string ssServiceName, const std::string& packet);
    int svc2port(std::string ssSvcName);
    std::string host2ipv4addr(const std::string& hostname);
};

// Window management and display
window * pWin = new window();
pWin->set_title("Application Title");
pWin->add_row("Content row");
pWin->render();