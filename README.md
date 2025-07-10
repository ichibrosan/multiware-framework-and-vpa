# Virtual Protocol Adapter & Multiware Framework (mwfw2)

[![License](https://img.shields.io/badge/License-All%20Rights%20Reserved-red.svg)](LICENSE)
[![Version](https://img.shields.io/badge/Version-5.5.10.2-blue.svg)](CHANGELOG)
[![C++](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)](https://isocpp.org/)

A comprehensive C++ framework providing Virtual Protocol Adapter (VPA) RPC services and multiware system capabilities for distributed computing environments.

## 📋 Detailed Description

The Virtual Protocol Adapter & Multiware Framework (mwfw2) is a sophisticated, enterprise-grade C++ framework designed for distributed computing environments. It provides a robust foundation for building secure, scalable applications with advanced RPC capabilities, comprehensive user management, and professional console-based interfaces.

### Core Architecture

The framework is built around two primary components that work seamlessly together:

#### 1. Virtual Protocol Adapter (VPA)
The VPA component provides a complete RPC infrastructure with the following capabilities:

**Authentication & Security:**
- **Pre-Shared Key (PSK) Authentication**: Secure initial authentication using configurable pre-shared keys
- **Token-Based Session Management**: Dynamic authentication tokens for ongoing session security
- **Multi-Level Authorization**: Role-based access control with configurable authorization levels
- **Session Handle Management**: Unique session identifiers for tracking and managing user sessions

**RPC Protocol Operations:**
- **VPARPC_FUNC_GET_AUTH**: Initial authentication and token acquisition
- **VPARPC_FUNC_VERSION**: Server version information retrieval
- **VPARPC_FUNC_LOOKUP**: User credential verification and session initiation
- **VPARPC_FUNC_CREDS**: Comprehensive user information and metadata retrieval

**Network Architecture:**
- **Standalone TCP Server**: Independent server process for dedicated RPC services
- **inetd/xinetd Integration**: System service integration for scalable deployment
- **Client-Server Communication**: Bi-directional structured data exchange
- **Multiple Service Endpoints**: Support for different service names and configurations

#### 2. Multiware Framework (mwfw2)
The mwfw2 component provides comprehensive system utilities and interface capabilities:

**Window Management System:**
- **Professional Console Interface**: Unicode box-drawing characters for sophisticated text-based UIs
- **Dynamic Window Rendering**: Flexible window sizing and content management
- **Title and Border Management**: Configurable window titles with professional styling
- **Content Row Management**: Dynamic addition and formatting of display content

**System Integration:**
- **Environment Detection**: Automatic CGI vs. console mode detection
- **Shared Memory Management**: Thread-safe shared memory operations with mutex protection
- **Configuration Management**: INI-style configuration with environment variable integration
- **Logging Infrastructure**: Multi-level logging with system log integration

**Utility Components:**
- **CSV Reading**: Structured data parsing and processing
- **Hex Dump Utilities**: Binary data visualization and analysis
- **Password Management**: Secure credential handling and validation
- **Schema Compilation**: Database schema processing and validation

### Advanced Features

**Database Integration:**
- **Schema Management**: Automated database schema compilation and validation
- **Query Processing**: Advanced SQL query building and execution
- **Data Binding**: Automatic data mapping between C++ objects and database records
- **Transaction Support**: Comprehensive transaction management with rollback capabilities

**Web Interface Support:**
- **CGI Integration**: Seamless web interface generation and processing
- **HTML Generation**: Dynamic HTML content creation with styling support
- **RESTful API Support**: HTTP-based API endpoints for web service integration
- **Session Management**: Web-based session tracking and user management

**Development & Debugging:**
- **Comprehensive Logging**: Multi-level logging with configurable output destinations
- **Diagnostic Utilities**: Built-in debugging and system analysis tools
- **Test Framework**: Integrated testing utilities for component validation
- **Performance Monitoring**: System resource monitoring and performance analysis

### Security Features

**Authentication Architecture:**
- **Multi-Factor Authentication**: PSK + credential-based authentication
- **Session Security**: Time-based session tokens with automatic expiration
- **Authorization Levels**: Granular permission control based on user roles
- **Audit Trail**: Comprehensive logging of authentication and authorization events

**Data Protection:**
- **Secure Communication**: Encrypted data transmission between client and server
- **Credential Management**: Secure storage and handling of user credentials
- **Input Validation**: Comprehensive validation of all user inputs and RPC parameters
- **Error Handling**: Secure error handling that prevents information leakage

### Deployment Options

**Standalone Deployment:**
- Independent server processes for dedicated RPC services
- Configurable network interfaces and port bindings
- Process management and monitoring capabilities
- Automatic restart and recovery mechanisms

**System Service Integration:**
- xinetd/inetd integration for on-demand service activation
- Systemd service file generation and management
- Automatic service discovery and registration
- Load balancing and failover capabilities

**Web Service Deployment:**
- CGI-based web interface deployment
- Apache/Nginx integration with mod_cgi
- RESTful API endpoint configuration
- SSL/TLS certificate management

### Use Cases

**Enterprise Applications:**
- Distributed authentication services for multi-system environments
- Centralized user management and credential verification
- Secure inter-system communication and data exchange
- Administrative dashboards and monitoring interfaces

**Development Environments:**
- Rapid prototyping of distributed applications
- Testing and validation of RPC-based systems
- Development tools and utilities for system administration
- Educational platforms for distributed computing concepts

**System Integration:**
- Legacy system modernization and API exposure
- Microservices architecture implementation
- Cross-platform communication bridge
- System monitoring and management tools

## 🚀 Features

### Virtual Protocol Adapter (VPA)
- **RPC Client/Server Architecture**: Full-featured remote procedure call system
- **Authentication System**: Secure PSK-based authentication with token management
- **User Management**: Complete user lookup, credential management, and authorization levels
- **Multiple Server Modes**: Standalone server and inetd-compatible server implementations
- **Session Management**: Handle-based session tracking and management

### Multiware Framework (mwfw2)
- **Window Management**: Advanced console-based window rendering system
- **Semi-Graphics Support**: Unicode box-drawing characters for professional UI
- **Logging System**: Comprehensive logging with multiple output targets
- **Configuration Management**: INI-based configuration with environment integration
- **Shared Memory Management**: Thread-safe shared memory operations
- **CGI Integration**: Web-based interface capabilities

## 📁 Project Structure